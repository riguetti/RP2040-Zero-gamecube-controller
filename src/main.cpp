#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"


#include "hardware/adc.h"


#include <vector>

#include "global.hpp"

#include "dac_algorithms/melee_F1.hpp"

#include "gpio_to_button_sets/F1.hpp"

#include "communication_protocols/joybus.hpp"

#include "other/runtime_remapping_mode.hpp"

int main() {
	
	


    set_sys_clock_khz(1000*us, true);
    stdio_init_all();
	
		
	adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
	adc_gpio_init(27);
    adc_gpio_init(28);
    adc_gpio_init(29);
	



    #if USE_UART0
    // Initialise UART 0
    uart_init(uart0, 115200);
 
    // Set the GPIO pin mux to the UART - 0 is TX, 1 is RX
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    #endif

    const uint8_t keyboardPin = 
    #if USE_UART0
    3
    #else
    0
    #endif
    ;

    std::vector<uint8_t> modePins = { 22, 21, 20, 16, 17, 14, 13, 7, 6, 5, 4, 2, keyboardPin }; // DO NOT USE PIN GP15

    for (uint8_t modePin : modePins) {
        gpio_init(modePin);
        gpio_set_dir(modePin, GPIO_IN);
        gpio_pull_up(modePin);
    }

    // 21 - GP16 - BOOTSEL
    if (!gpio_get(16)) reset_usb_boot(0, 0);

    // 22 - GP17 - Up : runtime remapping
    if (!gpio_get(17)) Other::enterRuntimeRemappingMode();
    
    gpio_init(gcDataPin);
    gpio_set_dir(gcDataPin, GPIO_IN);
    gpio_pull_up(gcDataPin);

    uint32_t origin = time_us_32();
    while ( time_us_32() - origin < 100'000 );
    while ( time_us_32() - origin < 500'000 ) {
        if (!gpio_get(gcDataPin)) goto stateLabel__forceJoybusEntry;
    }
    

        stateLabel__forceJoybusEntry:



        

        CommunicationProtocols::Joybus::enterMode(gcDataPin, [](){ return DACAlgorithms::MeleeF1::getGCReport(GpioToButtonSets::F1::defaultConversion()); });
    


}