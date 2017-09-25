package Tree; /**
 * Created by Gradergage on 12.05.2016.
 */

import java.util.*;

import Values.Colors;
import Values.Parameters;

import static Values.Parameters.GET_ARRAY;

public class RBtree<K extends Comparable, V> extends AbstractMap<K, V> {

    private Node root;
    private List<String> array;
    private int size;
    private V tempValue;
    private boolean result;
    private String toString;

    public RBtree() {
        array = new ArrayList<>();
        root = null;
        tempValue = null;
        result = false;
        size = 0;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        if (root == null && size == 0) {
            return true;
        } else {
            return false;
        }
    }
    // следующий элемент(по возрастанию ближайшего ключа), сложность O(logn)
    public Node successor(Node z) {
        if (z == null) {
            return null;
        } else if (z.getRight() != null) {
            return minimum(z.getRight());
        } else {
            return null;
        }
    }
    // предыдущий элемент (по убыванию ближайшего ключа), сложность O(logn)
    public Node predcessor(Node z) {

        if (z == null) {
            return null;
        } else if (z.getLeft() != null) {
            return maximum(z.getLeft());
        } else {
            return null;
        }
    }
    //сложность метода O(logn), сравнивая ключи мы должный обойти все дерево
    //по высоте, если ключ не найдем, то его нет
    public boolean containsKey(K key) {

        if (get(key) == null) {
            return false;
        } else {
            return true;
        }
    }

    @Override
    //сложность метода O(n), мы обязаны обойти все элементы
    public String toString() {
        toString = "";
        walk(root, Parameters.TO_STRING);

        return toString;
    }

    //сложность метода O(n), так как в худшем случае нам придется обойти все элементы
    @Override
    public boolean containsValue(Object value) {
        result = false;
        V val = (V) value;
        walk(root, Parameters.GET_VALUE);
        return result;
    }

    @Override
    public void clear() {

        if (root == null) {
            return;
        } else {
            root.setLeft(null);
            root.setRight(null);
            root = null;
            size = 0;
            return;
        }
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        throw new UnsupportedOperationException("Unsupported");
    }

    private Node getRoot() {
        return root;
    }

    public List<String> getArray() {
        array.clear();
        walk(root, Parameters.GET_ARRAY);
        return array;
    }

    //Меняет местами две вершины (без изменения цвета, что не нарушает структуру дерева) - O(1)
    private void replace(Node y, Node x) {
        if (y != null && x != null) {
            K k = (K) y.getKey();
            V v = (V) y.getValue();
            y.setKey(x.getKey());
            y.setValue(x.getValue());
            x.setKey(k);
            x.setValue(v);
        }
    }

    //Рекурсивная функция обхода, по сути обходит каждый элемент за один шаг, поэтому
    //сложность ее будет O(n)
    private void walk(Node z, Parameters target) {
        if (z != null) {
            walk(z.getLeft(), target);
            switch (target) {
                case GET_ARRAY: {
                    array.add(z.getKey().toString() + " " + z.getValue().toString());
                    break;
                }
                case TO_STRING: {
                    toString += z.getKey() + " ";
                    break;
                }
                case GET_VALUE: {
                    if (z.getValue() == tempValue) {
                        result = true;
                        return;
                    } else {
                        break;
                    }
                }
                default: {
                    return;
                }
            }
            walk(z.getRight(), target);
        }
    }

    //поиск сначала имеет сложность равную максимальной высоте дерева
    //или же O(n)
    public Node get(K key) {
        return search(root, key);
    }


    //поиск от заданной вершины, тоже O(n)
    private Node search(Node z, K key) {
        while (z != null && key != z.getKey()) {
            if (key.compareTo(z.getKey()) == -1) {
                z = z.getLeft();
            } else {
                z = z.getRight();
            }
        }
        return z;
    }

    //поиск соседа O(1)
    private Node neighbor(Node z) {
        if (z == null) {
            return null;
        }
        if (z == z.getParent().getLeft()) {
            return z.getParent().getRight();
        } else {

            return z.getParent().getLeft();
        }
    }

    //======НАЧАЛО БЛОКА ВСТАВКИ======
    //Цена вставки -  O(logn)
    public V put(K tempK, V tempV) {

        //проверка, есть ли такой ключ
        if (containsKey(tempK)) {
            System.out.println("This key already exist");
            return tempV;
        }

        Node z = new Node<K, V>(tempK, tempV);
        Node x = root;
        Node y = null;


        //Вставка корня
        if (root == null) {
            z.setColor(Colors.BLACK);
            root = z;
            size++;
            return null;
        } else {
            //Обычная вставка, узел z по умолчанию красный
            boolean right = true;
            while (x != null) {
                y = x;

                if (z.getKey().compareTo(x.getKey()) == 1) {
                    x = x.getRight();
                    right = true;
                } else {
                    x = x.getLeft();
                    right = false;
                }
                z.setParent(y);
            }
            if (right) {
                y.setRight(z);
            } else {
                y.setLeft(z);
            }
        }
        //корректировка
        insertFix(z);
        size++;
        return (V) z.getValue();
    }


    private void insertFix(Node temp) {
        if (temp.getParent() == null) {
            temp.setColor(Colors.BLACK);
            root = temp;
        } else {
            insertFix2(temp);
        }
    }

    private void insertFix2(Node temp) {
        if (temp.getParent().getColor() == Colors.BLACK) {
        } else {
            insertFix3(temp);
        }
    }

    private void insertFix3(Node temp) {


        if ((temp.getUncle() != null) && (temp.getUncle().getColor() == Colors.RED) && (temp.getParent().getColor() == Colors.RED)) {
            temp.getParent().setColor(Colors.BLACK);
            temp.getUncle().setColor(Colors.BLACK);
            temp.getGrandparent().setColor(Colors.RED);
            insertFix(temp.getGrandparent());
        } else {
            insertFix4(temp);
        }
    }

    private void insertFix4(Node temp) {
        if ((temp == temp.getParent().getRight()) && (temp.getParent() == temp.getGrandparent().getLeft())) {
            rotateLeft(temp.getParent());
            temp = temp.getLeft();
        } else if ((temp == temp.getParent().getLeft()) && (temp.getParent() == temp.getGrandparent().getRight())) {
            rotateRight(temp.getParent());
            temp = temp.getRight();
        }
        insertFix5(temp);
    }

    private void insertFix5(Node temp) {
        temp.getParent().setColor(Colors.BLACK);
        temp.getGrandparent().setColor(Colors.RED);
        if ((temp == temp.getParent().getLeft()) && (temp.getParent() == temp.getGrandparent().getLeft())) {
            rotateRight(temp.getGrandparent());
        } else {
            rotateLeft(temp.getGrandparent());
        }
    }
    //======КОНЕЦ БЛОКА ВСТАВКИ======


    //======НАЧАЛО БЛОКА УДАЛЕНИЯ====
    //удаление не корня, а конечного элемента с двумя листовыми потомками
    private V deleteNode(Node r) {

        V val;
        if (r == null) {
            return null;
        }
        //удаление чистого корня
        size--;
        if (r.getParent() == null && r.getLeft() == null && r.getRight() == null) {
            val = (V) r.getValue();
            r = null;
            root = null;
            return val;

        }

        if (r.getParent().getLeft() == r) {
            r.getParent().setLeft(null);
        } else {
            r.getParent().setRight(null);
        }
        val = (V) r.getValue();
        r = null;
        return val;
    }

    //начало функции удаления, удаление как и вставка занимает O(logn)
    public V remove(K key) {
        Node z = search(root, key);
        return delete0(z);
    }

    private V delete0(Node z) {

        if (z == null) {
            return null;
        }
        Node y;
        //проверка, если вершина имеет двух нелистовых потомков
        //после этого мы приходим к случаю удаления вершины с 1 нелистовым потомков
        if (z.getLeft() != null && z.getRight() != null) {
            y = maximum(z.getLeft());
            replace(z, y);
            return delete0(y);
            //если нет, то случай обычного удаления крайней вершины
        } else if (z.getLeft() == null && z.getRight() == null) {
            return deleteNode(z);

        } else {
            //или же удаление вершины содержащей 1 листового потомка
            return delete1(z);
        }
    }

    private V delete1(Node z) {
        if (z.getLeft() == null && z.getRight() == null) {
            deleteNode(z);
        }
        Node c;
        if (z.getRight() != null) {
            c= z.getRight();
        } else {
            c= z.getLeft();
        }
        //фикс цветов
        replace(z, c);
        if (z.getColor() == Colors.BLACK) {
            if (c.getColor() == Colors.RED) {
                c.setColor(Colors.BLACK);
            } else {
                deleteFix(c);
            }
        }
        //return val;
        return deleteNode(c);
    }

    //проверка, вдруг это корень
    private void deleteFix(Node z) {
        if (z.getParent() == null) {
            root = z;
        } else {
            deleteFix2(z);
        }
    }

    //случай, когда сосед красный
    private void deleteFix2(Node z) {
        Node n = neighbor(z);
        if (n.getColor() == Colors.RED) {
            z.getParent().setColor(Colors.RED);
            n.setColor(Colors.BLACK);
            if (z == z.getParent().getLeft()) {
                rotateLeft(z.getParent());
            } else {
                rotateRight(z.getParent());
            }
        }
        deleteFix3(z);
    }

    //случай когда родитель и сосед черный и дети его тоже черные, нарушается структура и мы должны перекрасить соседа в красный
    private void deleteFix3(Node z) {
        Node n = neighbor(z);
        if (z.getParent().getColor() == Colors.BLACK && n.getColor() == Colors.BLACK && n.getLeft().getColor() == Colors.BLACK && n.getRight().getColor() == Colors.BLACK) {
            n.setColor(Colors.RED);
            deleteFix(z.getParent());
        } else {
            deleteFix4(z);
        }
    }

    //то же самое что и сверху, но при этом еще и общий родитель красный
    private void deleteFix4(Node z) {
        Node n = neighbor(z);
        if (z.getParent().getColor() == Colors.RED && n.getColor() == Colors.BLACK && n.getLeft().getColor() == Colors.BLACK && n.getRight().getColor() == Colors.BLACK) {
            n.setColor(Colors.RED);
            z.getParent().setColor(Colors.BLACK);
        } else {
            deleteFix5(z);
        }

    }

    //если отец черный, а потомки-соседи - разного цвета, то нужно выполнить поворот, чтобы реализовать чередование цветов
    private void deleteFix5(Node z) {
        Node n = neighbor(z);
        if (n.getColor() == Colors.BLACK) {
            if (z == z.getParent().getLeft() && n.getRight().getColor() == Colors.BLACK && n.getLeft().getColor() == Colors.RED) {
                n.setColor(Colors.RED);
                n.getLeft().setColor(Colors.BLACK);
                rotateRight(n);
            } else if (z == z.getParent().getRight() && n.getLeft().getColor() == Colors.BLACK && n.getRight().getColor() == Colors.RED) {
                n.setColor(Colors.RED);
                n.getRight().setColor(Colors.BLACK);
                rotateLeft(n);
            }
        }
        deleteFix6(z);
    }

    //поворот дерева для уравновешивания цветов, если у черного дедушки есть два черных потомка и один внук красный
    private void deleteFix6(Node z) {
        Node n = neighbor(z);
        n.setColor(z.getParent().getColor());
        z.getParent().setColor(Colors.BLACK);
        if (z == z.getParent().getLeft()) {
            n.getRight().setColor(Colors.BLACK);
            rotateLeft(z.getParent());
        } else {
            n.getLeft().setColor(Colors.BLACK);
            rotateRight(z.getParent());
        }
    }
    //======КОНЕЦ БЛОКА УДАЛЕНИЯ======


    //сложность минимума и максиумуа O(logn)
    //равна высота дерева ( или поддерева )
    private Node minimum(Node z) {
        if (z == null) {
            return null;
        }
        while (z.getLeft() != null) {
            z = z.getLeft();
        }
        return z;
    }

    private Node maximum(Node z) {
        if (z == null) {
            return null;
        }
        while (z.getRight() != null) {
            z = z.getRight();
        }
        return z;
    }

    //====ПОВОРОТЫ====
    //повороты осуществляются за O(1)
    //           |              |
    //           y              x
    //         /   \    <-    /   \
    //        x     c       a      y
    //      /   \                /  \
    //    a      b              b    c
    private void rotateLeft(Node x) {
        Node y = x.getRight();
        y.setParent(x.getParent());
        if (x.getParent() == null) {
            root = y;
        }
        {
            if (x.getParent() != null) {
                if (x.getParent().getLeft() == x) {
                    x.getParent().setLeft(y);
                } else {
                    x.getParent().setRight(y);
                }
            }
            x.setRight(y.getLeft());
            if (y.getLeft() != null) {
                y.getLeft().setParent(x);
            }
            x.setParent(y);
            y.setLeft(x);
        }
    }
    //           |              |
    //           y              x
    //         /   \    ->    /   \
    //        x     c       a      y
    //      /   \                /  \
    //    a      b              b    c
    private void rotateRight(Node y) {
        Node x = y.getLeft();
        x.setParent(y.getParent());
        if (y.getParent() == null) {
            root = x;
        }
        {
            if (y.getParent() != null) {
                if (y.getParent().getLeft() == y) {
                    y.getParent().setLeft(x);
                } else {
                    y.getParent().setRight(x);
                }
            }
            y.setLeft(x.getRight());
            if (x.getRight() != null) {
                x.getRight().setParent(y);
            }
            y.setParent(x);
            x.setRight(y);
        }
    }
}
