package com.google.sample;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class MainActivity extends Activity {
    TextView status_view;
    private static final String LOG = MainActivity.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        status_view = (TextView)findViewById(R.id.statusView);

        // Create a hash map
        TreeMap tm = new TreeMap();

        // Put elements to the map
        ArrayList<Float> floats = new ArrayList<>();
        floats.add(2.3f);

        tm.put(1, new ArrayList<>(floats));
        tm.put(2, new ArrayList<>(floats));
        tm.put(3, new ArrayList<>(floats));
        tm.put(4, new ArrayList<>(floats));
        tm.put(5, new ArrayList<>(floats));

        int mapSize = NativeDeclarations.getPoints(tm);

        status_view.setText(Integer.toString(mapSize));

        // Get a set of the entries
        Set set = tm.entrySet();

        // Get an iterator
        Iterator i = set.iterator();

        // Display elements
        ArrayList<Float> buff;
        while(i.hasNext()) {
            Map.Entry me = (Map.Entry)i.next();
            Log.i(LOG, "Key :: " + me.getKey());
            buff = (ArrayList<Float>)me.getValue();
            if (buff == null) continue;
            for (Float f : buff) {
                Log.i(LOG, "Value :: " + f);
            }
        }

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_exit) {
            finish();
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    /*
     * Loading our Lib
     */
    static {
        System.loadLibrary("treeMap");
    }

}
