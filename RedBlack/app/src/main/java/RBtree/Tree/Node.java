package RBtree.Tree;

import RBtree.Values.Colors;

/**
 * Created by Gradergage on 12.05.2016.
 */
public class Node<K extends Comparable, V> {
    private Colors color;
    //  private String color;
    private K key;
    private V value;
    private Node left;
    private Node right;
    private Node parent;

    Node() {
        color = Colors.RED;
        key = null;
        value = null;
    }

    Node(K tempK, V tempV) {
        color = Colors.RED;
        key = tempK;
        value = tempV;
        left = null;
        right = null;
        parent = null;
    }

    Colors getColor() {
        return color;
    }


    K getKey() {
        if (this == null) {
            return null;
        }
        return key;
    }

    V getValue() {
        if (this == null) {
            return null;
        }
        return value;
    }

    Node getLeft() {
        return left;
    }

    Node getRight() {
        return right;
    }

    Node getParent() {
        return parent;
    }


    //Родитель родительского элемента
    Node getGrandparent() {
        if (this.getParent() != null) {
            return this.getParent().getParent();
        } else {
            return null;
        }
    }

    //Брат родительского элемента
    Node getUncle() {
        if (this.getGrandparent() != null) {
            if (this.getGrandparent().getLeft() == this) {
                return this.getGrandparent().getRight();
            } else {
                return this.getGrandparent().getLeft();
            }
        } else {
            return null;
        }

    }

    void setLeft(Node temp) {
        left = temp;
    }

    void setRight(Node temp) {
        right = temp;
    }

    void setParent(Node temp) {
        parent = temp;
    }

    void setColor(Colors temp) {
        color = temp;
    }

    void setKey(K temp) {
        key = temp;
    }

    void setValue(V temp) {
        value = temp;
    }

    public String show() {
        return this.getColor() + " " + this.getKey() + " " + this.getValue();
    }
}
