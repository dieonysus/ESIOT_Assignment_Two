package com.example.dashboard;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Logger {
    private static final String TEMPERATURE_LOG_FILE = "history/temperature_log.txt";
    private static final String PERCENTAGE_LOG_FILE = "history/percentage_log.txt";

    private static PrintWriter temperatureWriter;
    private static PrintWriter percentageWriter;

    static {
        try {
            temperatureWriter = new PrintWriter(new FileWriter(TEMPERATURE_LOG_FILE, true));
            percentageWriter = new PrintWriter(new FileWriter(PERCENTAGE_LOG_FILE, true));

            String sessionStart = "\n--- New Session Started: " + getCurrentTime() + " ---\n";

            temperatureWriter.println(sessionStart);
            percentageWriter.println(sessionStart);
            temperatureWriter.flush();
            percentageWriter.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void logTemperature(String temperature) {
        String currentTime = getCurrentTime();
        temperatureWriter.println(currentTime + " - " + temperature);
        temperatureWriter.flush();
    }

    public static void logPercentage(String percentage) {
        String currentTime = getCurrentTime();
        percentageWriter.println(currentTime + " - " + percentage);
        percentageWriter.flush();
    }

    private static String getCurrentTime() {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return sdf.format(new Date());
    }

    public static void close() {
        if (temperatureWriter != null) {
            temperatureWriter.close();
        }
        if (percentageWriter != null) {
            percentageWriter.close();
        }
    }
}
