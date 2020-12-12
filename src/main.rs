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
