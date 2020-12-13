#![no_std]
#![no_main]

// pick a panicking behavior
use panic_halt as _; // you can put a breakpoint on `rust_begin_unwind` to catch panics
// use panic_abort as _; // requires nightly
// use panic_itm as _; // logs messages over ITM; requires ITM support
// use panic_semihosting as _; // logs messages to the host stderr; requires a debugger

use stm32l4::stm32l4x6;
use cortex_m::peripheral::{syst, Peripherals};
use cortex_m_rt::entry;

#[entry]
fn main() -> ! {
    
    let mut peripherals = stm32l4x6::Peripherals::take().unwrap();
    let cort_peri = Peripherals::take().unwrap();
    let mut systick = cort_peri.SYST;
    let gpioa = &peripherals.GPIOA;
    let rcc = &peripherals.RCC;
    let usart = &peripherals.USART2;

    systick.set_clock_source(syst::SystClkSource::Core);
    systick.set_reload(500_000);
    systick.clear_current();
    systick.enable_counter();

    led::init(rcc, gpioa);

    loop {
        led::blink_led(gpioa);

        while !systick.has_wrapped() {}
    }
}


pub mod led {
    pub fn init(rcc: &stm32l4::stm32l4x6::RCC, gpioa: &stm32l4::stm32l4x6::GPIOA) {

        //turn clock on to GPIOA
        rcc.ahb2enr.modify(|_, w| w.gpioaen().set_bit());

        //set as outpout
        gpioa.moder.modify(|_, w| w.moder5().output());

        //no pull up no pull down
        gpioa.pupdr.modify(|_, w| w.pupdr5().floating());        
    }
    pub fn blink_led(gpioa: &stm32l4::stm32l4x6::GPIOA) {gpioa.odr.modify(|r, w| w.odr5().bit(!r.odr5().bit()));}

    pub fn turn_led_on(gpioa: &stm32l4::stm32l4x6::GPIOA) {gpioa.odr.modify(|_, w| w.odr5().high()); }

    pub fn turn_led_off(gpioa: &stm32l4::stm32l4x6::GPIOA) {gpioa.odr.modify(|_, w| w.odr5().low()); }
}


pub mod usart {
    pub fn rcc_init(rcc: &stm32l4::stm32l4x6::RCC) {
        rcc.cr.modify(|_, w| w.hsion().set_bit());
        
        //wait for HSI to be ready
        while !rcc.cr.read().hsirdy().bit() {}

        //set HSI as clock
        rcc.cfgr.modify(|_, w| unsafe {w.sw().bits(0b1)});

        while rcc.cfgr.read().sws().bits() == 0 {}

        //turn clock on to GPIOA
        rcc.ahb2enr.modify(|_, w| w.gpioaen().set_bit());

        //enable clock for usart2
        rcc.apb1enr1.modify(|_, w| w.usart2en().set_bit());
    }
    pub fn usart_init(usart: &stm32l4::stm32l4x6::USART2) {
        // set word length 8 bits
        usart.cr1.modify(|_, w| w.m0().set_bit());

        //set reciever
        usart.cr1.modify(|_, w| w.re().set_bit());

        //set transmitter
        usart.cr1.modify(|_, w| w.te().set_bit());

        //set parity 
        usart.cr1.modify(|_, w| w.ps().clear_bit());

        //set stop bits
        usart.cr2.modify(|_, w| w.stop().stop1());

        //Set Baud Rate
        // fck/USARTDIV for 16 bit sample
        // 8M/USARTDIV = Baudrate
        // BRR = USARTDIV in 16 bit mode
        usart.brr.modify(|_, w| w.brr().bits(0b1100000));

        //enable USART
        usart.cr1.modify(|_, w| w.ue().set_bit());

        //enable recieved data ready interrupt
        usart.cr1.modify(|_, w| w.rxneie().set_bit());
    }

    pub fn usart_write(usart: &stm32l4::stm32l4x6::USART2, buffer: [u16; 5]) {

        for element in buffer.iter() { 
            //wait until TXE is set
            while !usart.isr.read().txe().bit() {}
            //write buffer out
            usart.tdr.write(|w| unsafe { w.tdr().bits(element & 0x1FF)}) 
        }
        // wait until transmission complete
        while ! usart.isr.read().tc().bit() {}

        // clear transmission complete flag
        usart.icr.write(|w| w.tccf().clear_bit());

    }
}
