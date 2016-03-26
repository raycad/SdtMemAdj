package com.seedotech.sdtmemadj;

import android.app.ActivityManager;
import android.content.Context;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private Context mContext;
    private TextView mTvMemInfo;
    private TextView mTvMemHeap;
    private EditText mEdtMemAdj;

    public native int nativeInitMemAdj();

    public native int nativeDeInitMemAdj();

    public native int nativeIncreaseMem(int mbSize);

    public native int nativeDecreaseMem(int mbSize);

    protected void initUI() {
        mTvMemInfo = (TextView) findViewById(R.id.tv_mem_info);
        mTvMemHeap = (TextView) findViewById(R.id.tv_mem_heap);
        mEdtMemAdj = (EditText) findViewById(R.id.edt_mem_adj);
        mEdtMemAdj.setText("50");
        Button btn = (Button) findViewById(R.id.btn_refresh_mem_info);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                refreshMemInfo();
            }
        });

        btn = (Button) findViewById(R.id.btn_increase_mem);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    int size = nativeIncreaseMem(Integer.parseInt(mEdtMemAdj.getText().toString()));
                    mTvMemHeap.setText(String.format("Current MEM heap: %d (MB)", size));
                    refreshMemInfo();
                } catch (Exception e) {
                    Toast.makeText(mContext, e.toString(),
                            Toast.LENGTH_LONG).show();
                }
            }
        });

        btn = (Button) findViewById(R.id.btn_decrease_mem);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    int size = nativeDecreaseMem(Integer.parseInt(mEdtMemAdj.getText().toString()));
                    if (size < 0)
                        size = 0;
                    mTvMemHeap.setText(String.format("Current MEM heap: %d (MB)", size));
                    refreshMemInfo();
                } catch (Exception e) {
                    Toast.makeText(mContext, e.toString(),
                            Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    protected void refreshMemInfo() {
        ActivityManager.MemoryInfo mi = new ActivityManager.MemoryInfo();
        ActivityManager activityManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
        activityManager.getMemoryInfo(mi);
        long availableMegs = mi.availMem / 1048576;
        long totalMegs = mi.totalMem / 1048576;
        mTvMemInfo.setText(String.format("Memory Information: \nTotal MEM: %d (MB)\nAvailable MEM: %d (MB)",
                totalMegs, availableMegs));
    }

    protected void init() {
        mContext = this;
        try {
            System.loadLibrary("sdtmemadj");
            nativeInitMemAdj();
        } catch (Exception e) {
            Toast.makeText(mContext, e.toString(),
                    Toast.LENGTH_LONG).show();
        }
        initUI();
        refreshMemInfo();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        init();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
