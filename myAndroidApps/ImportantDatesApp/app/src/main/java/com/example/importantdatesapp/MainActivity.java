package com.example.importantdatesapp;

import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.OutputStream;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;


public class MainActivity extends AppCompatActivity {
    DatabaseHelper myDb;
    EditText editEventName, editEventDate;
    Button btnAddEvent, btnShowEvents;
    TextView txtEvents;
    Button btnExportDb, btnImportDb;

    private ActivityResultLauncher<Intent> exportLauncher;

    public Date parseDate(String dateStr) {
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
            return sdf.parse(dateStr);
        } catch (ParseException e) {
            e.printStackTrace();
            return null; // Return null if parsing fails
        }
    }
    private void chooseExportLocation() {
        Intent intent = new Intent(Intent.ACTION_CREATE_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("application/octet-stream");
        intent.putExtra(Intent.EXTRA_TITLE, "backup.db");
        exportLauncher.launch(intent);
    }

    private void exportDatabase(Uri uri) {
        File dbFile = getDatabasePath("ImportantDates.db");

        try (FileInputStream fis = new FileInputStream(dbFile);
             OutputStream os = getContentResolver().openOutputStream(uri)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                os.write(buffer, 0, bytesRead);
            }

            Toast.makeText(this, "Database exported successfully!", Toast.LENGTH_SHORT).show();

        } catch (IOException e) {
            e.printStackTrace();
            Toast.makeText(this, "Export failed!", Toast.LENGTH_SHORT).show();
        }
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myDb = new DatabaseHelper(this);

        editEventName = findViewById(R.id.editEventName);
        editEventDate = findViewById(R.id.editEventDate);
        btnAddEvent = findViewById(R.id.btnAddEvent);
        btnShowEvents = findViewById(R.id.btnShowEvents);
        txtEvents = findViewById(R.id.txtEvents);

        btnExportDb = findViewById(R.id.btnExportDb);
        btnImportDb = findViewById(R.id.btnImportDb);

        exportLauncher = registerForActivityResult(
                new ActivityResultContracts.StartActivityForResult(),
                result -> {
                    if (result.getResultCode() == RESULT_OK && result.getData() != null) {
                        exportDatabase(result.getData().getData());
                    }
                });
        btnExportDb.setOnClickListener(view -> chooseExportLocation());

        addEvent();
        showEvents();
    }

    private void addEvent() {
        btnAddEvent.setOnClickListener(view -> {
            boolean isInserted = myDb.insertData(editEventName.getText().toString(), editEventDate.getText().toString());
            if (isInserted) {
                Toast.makeText(MainActivity.this, "Event Added", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(MainActivity.this, "Error Adding Event", Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void showEvents() {
        btnShowEvents.setOnClickListener(view -> {
            Cursor res = myDb.getAllData();

            if (res.getCount() == 0) {
                //txtEvents.setText("No events found.");
                return;
            }
            List<Event> eventList = new ArrayList<>();
            while (res.moveToNext()) {
                String name = res.getString(1); // Assuming name is at column index 1
                Date date = parseDate(res.getString(2)); // Assuming date is at column index 2
                eventList.add(new Event(name, date));
            }
            res.close();
            Collections.sort(eventList, (e1, e2) -> e2.getDate().compareTo(e1.getDate()));
            StringBuilder buffer = new StringBuilder();
            for (Event event : eventList) {
                //System.out.println(event.getName() + " - " + event.getDate());
                buffer.append(event.getName()).append(":").append((event.dateString()));
                buffer.append("\n");
            }
            txtEvents.setText(buffer.toString());
        });
    }
}
