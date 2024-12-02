package com.example.dashboard;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Logger {
    private static final String TEMPERATURE_LOG_FILE = "history/temperature_log.txt";
    private static final String PERCENTAGE_LOG_FILE = "history/percentage_log.txt";

    public static void logTemperature(String temperature) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(TEMPERATURE_LOG_FILE, true))) {
            String currentTime = getCurrentTime();
            writer.println(currentTime + " - " + temperature);
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void logPercentage(String percentage) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(PERCENTAGE_LOG_FILE, true))) {
            String currentTime = getCurrentTime();
            writer.println(currentTime + " - " + percentage);
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String getCurrentTime() {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return sdf.format(new Date());
    }
}
