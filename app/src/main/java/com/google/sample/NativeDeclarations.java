package com.google.sample;

import java.util.ArrayList;
import java.util.TreeMap;

/**
 * jni native functions
 */
public class NativeDeclarations {

    public static native int getPoints(TreeMap<Integer, ArrayList<Float>> dataMap);

}
