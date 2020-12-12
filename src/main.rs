#![no_std]
#![no_main]

// pick a panicking behavior
use panic_halt as _; // you can put a breakpoint on `rust_begin_unwind` to catch panics
// use panic_abort as _; // requires nightly
// use panic_itm as _; // logs messages over ITM; requires ITM support
// use panic_semihosting as _; // logs messages to the host stderr; requires a debugger

use stm32l4::stm32l4x6;
use cortex_m_rt::entry;

#[entry]
fn main() -> ! {
    
    let mut peripherals = stm32l4x6::Peripherals::take().unwrap();
    let gpioa = &peripherals.GPIOA;
    let usart = &peripherals.USART2;

    loop {
        led::turn_led_on(gpioa);

        led::turn_led_off(gpioa);
    }
}


pub mod led {
    pub fn blink_led(gpioa: &stm32l4::stm32l4x6::GPIOA) {gpioa.odr.modify(|_, w| w.odr5().set_bit());}

    pub fn turn_led_on(gpioa: &stm32l4::stm32l4x6::GPIOA) {gpioa.odr.modify(|_, w| w.odr5().set_bit()); }

    pub fn turn_led_off(gpioa: &stm32l4::stm32l4x6::GPIOA) {gpioa.odr.modify(|_, w| w.odr5().clear_bit()); }
}


pub mod usart {
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
    
    }

    pub fn usart_read(usart: &stm32l4::stm32l4x6::USART2) {
        // to do: implement read functionality
    }
}