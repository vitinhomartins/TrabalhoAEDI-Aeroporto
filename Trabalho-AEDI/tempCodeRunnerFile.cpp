    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600)/60;
    int seconds = totalSeconds % 60;
    
    string h = (hours < 10 ? "0" : "") + to_string(hours);
    string m = (minutes < 10 ? "0" : "") + to_string(minutes);
    string s = (seconds < 10 ? "0" : "") + to_string(seconds);
    return h + ":" + m + ":" + s;
}