# To Do

### Low battery Warning

If running from battery, when charge gets too low the magnet will disengage and the gate will drop. This has potential safety ramifications.

Desired behaviour: if the charge is dropping at a rate which will soon be too low to hold the gate (15 minutes?) give an audible low battery warning.

### Gate position sensor

There is a circuit implemented to detect gate position (SENSOR_1) by way of a reed switch or similar, but no code to handle this.

Desired behaviour: if the switch is closed (gate up), engage the magnet.
