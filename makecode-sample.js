input.onButtonPressed(Button.A, function () {
    serial.writeLine("command")
    basic.pause(10000)
    serial.writeLine("takeoff")
})
serial.redirect(
SerialPin.P0,
SerialPin.P1,
BaudRate.BaudRate115200
)