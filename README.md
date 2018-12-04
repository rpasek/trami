Dear github user,
I created this project to keep track how much milk my daughter was consuming. 
The hope is to build a bunch of small sensors out of flex pcb and stick them on to the side of Medela milk bottles.

I searched for cheap BLE enabled MCU's and I found that the PSoC4 was a good match as it also has capsense which will make sensing quite cheap and simple.

So far this project is based on a couple of shields from Cypress plugged into each other:
* CY8CKIT-042-BLE(http://www.cypress.com/documentation/development-kitsboards/cy8ckit-042-ble-bluetooth-low-energy-ble-pioneer-kit)
* CY8CKIT-022 (http://www.cypress.com/documentation/development-kitsboards/cy8ckit-022-capsense-liquid-level-sensing-shield)

You'll need to remove R47 on CY8CKIT-042-BLE as it's hooked up to some USB to i2c converter thingy (and this hurts the capsense signal)

Use cases:
* Milk in to bank
* Milk out of bank
* Total milk in bank
* Discarding milk
* Freezing of milk
* Temperature of Milk
* Multiple banks
* Allow bottles to be washed without getting false readings
* Time and duration of feeding?
* Naming of each bottle

Ideas:
* Recharge with solar panel
* Run off a super capacitor rather then using a coin cell

Problems:
* If the flex pcb is a sticker on the bottle, how do you wash the bottle?
* Will an alkaline coin cell suck in the fridge? How about the freezer?
* Can Bluetooth get through a fridge door?
* How can bottles be named?

Things I broke:
* CapSense_Sleep and CapSense_Wakeup. The manual (used for detecting liquid level) version of CapSense doesn't appear to have these functions.
* Low power mode. I disabled the ENABLE_LOW_POWER_MODE flag because UART and CapSense were not being respected before going to sleep

Ok bye,
Richard