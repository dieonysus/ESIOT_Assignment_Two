package com.example.dashboard;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.util.Random;

public class Dashboard extends Application {

    @Override
    public void start(Stage primaryStage) {

        Button greenButton = new Button("EMPTY");
        Button redButton = new Button("RESTORE");

        String buttonStyle = "-fx-background-color: #247BA0; -fx-text-fill: white; -fx-font-size: 14px; -fx-font-weight: bold; -fx-background-radius: 5;";
        greenButton.setStyle(buttonStyle);
        redButton.setStyle("-fx-background-color: #FF1654; -fx-text-fill: white; -fx-font-size: 14px; -fx-font-weight: bold; -fx-background-radius: 5;");

        double buttonWidth = 170;
        double buttonHeight = 120;
        greenButton.setPrefSize(buttonWidth, buttonHeight);
        redButton.setPrefSize(buttonWidth, buttonHeight);

        Color rectangleColor = Color.web("#A8DADC");

        TextField percentTextField = new TextField();
        percentTextField.setPrefSize(170, 40);
        percentTextField.setStyle("-fx-background-color: #A8DADC; -fx-border-color: transparent;");
        percentTextField.setEditable(false);
        percentTextField.setText("0%");
        percentTextField.setAlignment(Pos.CENTER);

        TextField tempTextField = new TextField();
        tempTextField.setPrefSize(170, 40);
        tempTextField.setStyle("-fx-background-color: #A8DADC; -fx-border-color: transparent;");
        tempTextField.setEditable(false);
        tempTextField.setText("0°C");
        tempTextField.setAlignment(Pos.CENTER);


        Label tempLabel = new Label("Level of waste");
        tempLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold;");

        Label percentLabel = new Label("Temperature");
        percentLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold;");

        VBox tempVBox = new VBox(5);
        tempVBox.setAlignment(Pos.CENTER_LEFT);
        tempVBox.getChildren().addAll(tempLabel, percentTextField);
        VBox.setMargin(tempTextField, new javafx.geometry.Insets(0, 0, 20, 0));
        tempVBox.getChildren().add(greenButton);

        VBox percentVBox = new VBox(5);
        percentVBox.setAlignment(Pos.CENTER_LEFT);
        percentVBox.getChildren().addAll(percentLabel, tempTextField);
        VBox.setMargin(percentTextField, new javafx.geometry.Insets(0, 0, 20, 0));
        percentVBox.getChildren().add(redButton);

        HBox buttonBox = new HBox(20);
        buttonBox.getChildren().addAll(tempVBox, percentVBox);
        buttonBox.setAlignment(Pos.CENTER);

        VBox vBox = new VBox();
        vBox.getChildren().addAll(buttonBox);
        vBox.setAlignment(Pos.BOTTOM_CENTER);
        VBox.setMargin(buttonBox, new javafx.geometry.Insets(0, 0, 20, 0));

        Scene scene = new Scene(vBox, 400, 260);
        primaryStage.setTitle("Dashboard");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);

        greenButton.setOnAction(event -> percentTextField.setText("Hello"));
        redButton.setOnAction(event -> tempTextField.setText("Hello"));

        new Thread(() -> {
            Random random = new Random();
            while (true) {
                try {
                    Thread.sleep(2000);

                    String newPercent = random.nextInt(101) + "%";
                    String newTemp = random.nextInt(100) + "°C";
                    
                    Platform.runLater(() -> {
                        percentTextField.setText(newPercent);
                        tempTextField.setText(newTemp);
                    });
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();

        primaryStage.show();
        vBox.requestFocus();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
