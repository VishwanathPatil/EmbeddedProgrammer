package com.example.importantdatesapp;

import androidx.annotation.NonNull;

import java.util.Date;

public class Event {
    private String name;
    private Date date;

    public Event(String name, Date date) {
        this.name = name;
        this.date = date;
    }

    public String getName() {
        return name;
    }

    public Date getDate() {
        return date;
    }
    public String dateString() {
        // Convert the Date object to a formatted string
        return date.getDate() + "-"
                + (date.getMonth() + 1) + "-"
                + (1900 + date.getYear());
    }
}