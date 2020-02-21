#include <PS4Controller.h>

void setup()
{
    Serial.begin(115200);
    PS4.begin("e8:61:7e:c7:bf:36");
    Serial.println("Ready.");
}

void loop()
{
		// Below has all accessible outputs from the controller
    if(PS4.isConnected()) {
			if ( PS4.data.button.up )
					Serial.println("Up Button");
			if ( PS4.data.button.down )
					Serial.println("Down Button");
			if ( PS4.data.button.left )
					Serial.println("Left Button");
			if ( PS4.data.button.right )
					Serial.println("Right Button");
      if ( PS4.data.button.circle )
          Serial.println("Circle Button");
      if ( PS4.data.button.cross )
          Serial.println("Cross Button");

     if (PS4.data.status.charging)
        Serial.println("The controller is charging");
     if (PS4.data.status.audio)
        Serial.println("The controller has headphones attached");
     if (PS4.data.status.mic)
        Serial.println("The controller has a mic attached");

     Serial.print("Battey Percent : ");
     Serial.println(PS4.data.status.battery, DEC);

		 Serial.println();
		 // This delay is to make the Serial Print more human readable
		 // Remove it when you're not trying to see the output
     delay(1000);
    }
}
