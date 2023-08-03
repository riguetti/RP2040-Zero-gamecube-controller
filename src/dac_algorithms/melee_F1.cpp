#include "dac_algorithms/melee_F1.hpp"
#include "communication_protocols/joybus.hpp"
#include "hardware/adc.h"
namespace DACAlgorithms {
namespace MeleeF1 {

#define coord(x) ((uint8_t)(128. + 80.*x + 0.5))
#define oppositeCoord(x) -((uint8_t)x)

bool banParasolDashing = false;
bool banSlightSideB = false;

// 2 IP declarations
bool left_wasPressed = false;
bool right_wasPressed = false;
bool up_wasPressed = false;
bool down_wasPressed = false;

bool left_outlawUntilRelease = false;
bool right_outlawUntilRelease = false;
bool up_outlawUntilRelease = false;
bool down_outlawUntilRelease = false;

struct Coords {
    uint8_t x;
    uint8_t y;
};

Coords coords(float xFloat, float yFloat) {
    Coords r;
    r.x = coord(xFloat);
    r.y = coord(yFloat);
    return r;
}


GCReport getGCReport(GpioToButtonSets::F1::ButtonSet buttonSet) {
    
    GpioToButtonSets::F1::ButtonSet bs = buttonSet; // Alterable copy

    GCReport gcReport = defaultGcReport;

    /* 2IP No reactivation */
    
    if (left_wasPressed && bs.left && bs.right && !right_wasPressed) left_outlawUntilRelease=true;
    if (right_wasPressed && bs.left && bs.right && !left_wasPressed) right_outlawUntilRelease=true;
    if (up_wasPressed && bs.up && bs.down && !down_wasPressed) up_outlawUntilRelease=true;
    if (down_wasPressed && bs.up && bs.down && !up_wasPressed) down_outlawUntilRelease=true;

    if (!bs.left) left_outlawUntilRelease=false;
    if (!bs.right) right_outlawUntilRelease=false;
    if (!bs.up) up_outlawUntilRelease=false;
    if (!bs.down) down_outlawUntilRelease=false;

    left_wasPressed = bs.left;
    right_wasPressed = bs.right;
    up_wasPressed = bs.up;
    down_wasPressed = bs.down;

    if (left_outlawUntilRelease) bs.left=false;
    if (right_outlawUntilRelease) bs.right=false;
    if (up_outlawUntilRelease) bs.up=false;
    if (down_outlawUntilRelease) bs.down=false;
    
    /* Stick */

    bool vertical = bs.up || bs.down;
    bool readUp = bs.up;

    bool horizontal = bs.left || bs.right;
    bool readRight = bs.right;

    Coords xy;

    if (vertical && horizontal) {
        if (bs.l || bs.r) {
            if (bs.mx == bs.my) xy = coords(0.7, readUp ? 0.7 : 0.6875);
            else if (bs.mx) xy = coords(0.6375, 0.375);
            else xy = (banParasolDashing && readUp) ? coords(0.475, 0.875) : coords(0.5, 0.85);
        }
        else if (bs.b && (bs.mx != bs.my)) {
            if (bs.mx) {
                if (bs.cDown) xy = coords(0.9125, 0.45);
                else if (bs.cLeft) xy = coords(0.85, 0.525);
                else if (bs.cUp) xy = coords(0.7375, 0.5375);
                else if (bs.cRight) xy = coords(0.6375, 0.5375);
                else xy = coords(0.9125, 0.3875);
            }
            else {
                if (bs.cDown) xy = coords(0.45, 0.875);
                else if (bs.cLeft) xy = coords(0.525, 0.85);
                else if (bs.cUp) xy = coords(0.5875, 0.8);
                else if (bs.cRight) xy = coords(0.5875, 0.7125);
                else xy = coords(0.3875, 0.9125);
            }
        }
        else if (bs.mx != bs.my) {
            if (bs.mx) {
                if (bs.cDown) xy = coords(0.7, 0.3625);
                else if (bs.cLeft) xy = coords(0.7875, 0.4875);
                else if (bs.cUp) xy = coords(0.7, 0.5125);
                else if (bs.cRight) xy = coords(0.6125, 0.525);
                else xy = coords(0.7375, 0.3125);
            }
            else {
                if (bs.cDown) xy = coords(0.3625, 0.7);
                else if (bs.cLeft) xy = coords(0.4875, 0.7875);
                else if (bs.cUp) xy = coords(0.5125, 0.7);
                else if (bs.cRight) xy = coords(0.6375, 0.7625);
                else xy = coords(0.3125, 0.7375);
            }
        }
        else xy = coords(0.7,0.7);
    }
    else if (horizontal) {
        if (bs.mx == bs.my) xy = coords(1.0, 0.0);
        else if (bs.mx) xy =  (buttonSet.left && buttonSet.right) ? coords(1.0, 0.0) : coords(0.6625, 0.0);
        else xy = ((banSlightSideB && bs.b) || buttonSet.left && buttonSet.right) ? coords(1.0, 0.0) : coords(0.3375, 0.0);
        // Read the original rectangleInput to bypass SOCD
    }
    else if (vertical) {
        if (bs.mx == bs.my) xy = coords(0.0, 1.0);
        else if (bs.mx) xy=coords(0.0, 0.5375);
        else xy = coords(0.0, 0.7375);
    }
    else {
        xy = coords(0.0, 0.0);
    }

    if (horizontal && !readRight) xy.x = oppositeCoord(xy.x);
    if (vertical && !readUp) xy.y = oppositeCoord(xy.y);







    /* Stick */

    adc_select_input(2);
    uint stickX = adc_read();
    adc_select_input(3);
    uint stickY = adc_read();

    if (stickX > 3180) {
        stickX = 3180;
    }
    if (stickX < 965) {
        stickX = 965;
    }
    if (stickY > 3180) {
        stickY = 3180;
    }
    if (stickY < 965) {
        stickY = 965;
    }


    int valorStrickX = ((stickX - 965) * 192) / 2215 + 32;
    int valorStrickY = ((stickY - 965) * 192) / 2215 + 32;

    if (valorStrickX > 224) {
        valorStrickX = 224;
    }
    if (valorStrickX < 32) {
        valorStrickX = 32;
    }
    if (valorStrickY > 224) {
        valorStrickY = 224;
    }
    if (valorStrickY < 32) {
        valorStrickY = 32;
    }


    gcReport.xStick = valorStrickX;
    gcReport.yStick = valorStrickY;

    /* C-Stick */
    
    adc_select_input(1);
    uint stickCX = adc_read();
    adc_select_input(0);
    uint stickCY = adc_read();

    if (stickCX > 3180) {
        stickCX = 3180;
    }
    if (stickCX < 965) {
        stickCX = 965;
    }
    if (stickCY > 3180) {
        stickCY = 3180;
    }
    if (stickCY < 965) {
        stickCY = 965;
    }


    int valorCStrickX = ((stickCX - 965) * 192) / 2215 + 32;
    int valorCStrickY = ((stickCY - 965) * 192) / 2215 + 32;

    if (valorCStrickX > 224) {
        valorCStrickX = 224;
    }
    if (valorCStrickX < 32) {
        valorCStrickX = 32;
    }
    if (valorCStrickY > 224) {
        valorCStrickY = 224;
    }
    if (valorCStrickY < 32) {
        valorCStrickY = 32;
    }


    gcReport.cyStick = valorCStrickX;
    gcReport.cxStick = valorCStrickY;

    /* Dpad */
 
		
        gcReport.dDown = bs.down;
        gcReport.dLeft = bs.left;
        gcReport.dUp = bs.up;
        gcReport.dRight = bs.right;
    

    /* Triggers */

    gcReport.analogL = bs.l ? 224 : 0;
    gcReport.analogR = bs.r ? 224 : 0;

    /* Buttons */
    gcReport.a = bs.a;
    gcReport.b = bs.b;
    gcReport.x = bs.x;
    gcReport.y = bs.y;
    gcReport.z = bs.z;
    gcReport.l = bs.l;
    gcReport.r = bs.r;
    gcReport.start = bs.start;
	

    return gcReport;
}

}
}