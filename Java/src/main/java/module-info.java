module com.example.weaselprogram {
    requires javafx.controls;
    requires javafx.fxml;

    opens com.example.weaselprogram to javafx.fxml;
    exports com.example.weaselprogram;

}