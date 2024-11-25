package com.example.dashboard;

public class TestPingPong {

    public static void main(String[] args) throws Exception {

        CommChannel channel = new SerialCommChannel("COM3",9600);

        // CommChannel channel = new SerialCommChannel("/dev/cu.usbmodem1411",9600);


        /* Waiting Arduino rebooting */

        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Ready.");

        System.out.println("Done. Let's start.");

        while (true){
            System.out.println("Sending ping");
            channel.sendMsg("ping");
            String msg = channel.receiveMsg();
            System.out.println("Received: "+msg);
            Thread.sleep(500);
        }
    }
}
