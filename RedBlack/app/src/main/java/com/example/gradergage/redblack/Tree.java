package com.example.gradergage.redblack;

import android.app.Fragment;
import android.app.FragmentManager;
import android.content.Intent;
import android.nfc.FormatException;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

import RBtree.Tree.RBtree;

public class Tree extends AppCompatActivity {

    private RetainedFragment dataList;
    ListView listView;
    RBtree<Integer, String> tree;
    Button addButton;
    Button delete;
    EditText editKey;
    EditText editValue;
    ArrayList<String> keys;
    ArrayList<String> values;
    ArrayAdapter<String> adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tree);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        tree = new RBtree();
        editKey = (EditText) findViewById(R.id.editKey);
        editValue = (EditText) findViewById(R.id.editValue);
        listView = (ListView) findViewById(R.id.listView);
        addButton = (Button) findViewById(R.id.buttonAdd);
        delete = (Button) findViewById(R.id.buttonDelete);
        keys = new ArrayList<String>();

        //хранение данных при изменении activity
        FragmentManager fm = getFragmentManager();
        dataList = (RetainedFragment) fm.findFragmentByTag("data");

        if (tree == null) {
            dataList = new RetainedFragment();
            fm.beginTransaction().add(dataList, "data").commit();
            dataList.setData(keys);
            dataList.setDataTree(tree);
        }
        if (dataList == null) {
            dataList = new RetainedFragment();
            fm.beginTransaction().add(dataList, "data").commit();
            dataList.setData(keys);
            dataList.setDataTree(tree);
        }

        keys = dataList.getData();
        tree = dataList.getDataTree();

        adapter = new ArrayAdapter<String>(getApplicationContext(),
                R.layout.custom_list_view, keys);
        listView.setAdapter(adapter);
        adapter.notifyDataSetChanged();
        //вставка
        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                keys.clear();
                int key;
                String value;
                try {
                    key = Integer.parseInt(editKey.getText().toString());
                    value = editValue.getText().toString();
                    tree.put(key, value);
                } catch (NumberFormatException e) {
                    Toast toast = Toast.makeText(getApplicationContext(), R.string.error, Toast.LENGTH_SHORT);
                    toast.show();
                }

                editValue.setText("");
                editKey.setText("");


                List<String> temp = tree.getArray();


                for (int i = 0; i < temp.size(); i++) {
                    keys.add(temp.get(i));
                    adapter.notifyDataSetChanged();
                }
                dataList.setData(keys);
                dataList.setDataTree(tree);
            }
        });

        //удаление
        delete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                keys.clear();
                int key;
                try {
                    key = Integer.parseInt(editKey.getText().toString());
                    tree.remove(key);
                } catch (NumberFormatException e) {
                    Toast toast = Toast.makeText(getApplicationContext(), R.string.error1, Toast.LENGTH_SHORT);
                    toast.show();
                }
                editValue.setText("");
                editKey.setText("");


                List<String> temp = tree.getArray();

                if (temp == null)
                    keys.clear();
                for (int i = 0; i < temp.size(); i++) {
                    keys.add(temp.get(i));
                    adapter.notifyDataSetChanged();
                }
                adapter.notifyDataSetChanged();

                dataList.setData(keys);
                dataList.setDataTree(tree);
            }


        });

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        // store the data in the fragment
        dataList.setData(keys);
    }

    public class RetainedFragment extends Fragment {

        // data object we want to retain
        private ArrayList<String> data;
        private RBtree<Integer, String> dataT;

        // this method is only called once for this fragment
        @Override
        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            // retain this fragment
            data = new ArrayList<String>();
            dataT = new RBtree<>();
            setRetainInstance(true);
        }

        public void setData(ArrayList<String> data) {
            this.data = data;
        }

        public ArrayList<String> getData() {
            return data;
        }

        public RBtree getDataTree() {
            return dataT;
        }

        public void setDataTree(RBtree data) {
            this.dataT = data;
        }
    }

}
