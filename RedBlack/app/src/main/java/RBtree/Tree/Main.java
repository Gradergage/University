package Tree;


import junit.framework.TestCase;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import sun.reflect.generics.tree.Tree;

import java.util.*;

import static junit.framework.TestCase.assertEquals;
import static org.junit.Assert.assertTrue;

/**
 * Created by Gradergage on 13.05.2016.
 */
public class Main {
    public static void main(String[] args) {
        TestClass test = new TestClass();
        test.test1();
    }

    static class TestClass extends TestCase {
        private RBtree testTree;

        public TestClass() {
            testTree = new RBtree<Integer, String>();
        }

        @Test
        public void test1() {
            Assert.assertTrue(testTree.isEmpty());
            testTree.put(1, "kek");
            Assert.assertTrue(testTree.containsKey(1));
            Assert.assertFalse(testTree.containsValue("zez"));
            Assert.assertEquals(1, testTree.size());
            Assert.assertNull(testTree.get(13));
            Assert.assertEquals("kek", testTree.remove(1));
            Assert.assertTrue(testTree.isEmpty());
        }
    }
}
