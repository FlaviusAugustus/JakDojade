#include <fstream>
#include <string>
#include "gtest/gtest.h"
#include "../List/List.h"
#include "../String/String.h"
#include "../HashMap/HashMap.h"
#include "../PriorityQueueDijkstra/PriorityQueueDijkstra.h"

TEST(LIST_TEST, LinkedList_Construct) {

    List<int> list;

    ASSERT_EQ(list.length(), 0);
    ASSERT_EQ(list.getFirst(), nullptr);
    ASSERT_EQ(list.getFirst(), nullptr);

}

TEST(LIST_TEST, LinkedList_AddFirst) {

    List<int> list;
    list.addFirst(1);

    ASSERT_EQ(list.getFirst(), list.getLast());
    ASSERT_EQ(list.length(), 1);
    ASSERT_NE(list.getFirst(), nullptr);
    ASSERT_NE(list.getLast(), nullptr);
    ASSERT_EQ(list.getFirst()->data, 1);
    ASSERT_EQ(list.getLast()->data, 1);

    list.addFirst(2);

    ASSERT_EQ(list.length(), 2);
    ASSERT_NE(list.getFirst(), list.getLast());
    ASSERT_EQ(list.getFirst()->data, 2);
    ASSERT_EQ(list.getLast()->data, 1);

}

TEST(LIST_TEST, LinkedList_AddLast) {

    List<int> list;
    list.pushBack(1);

    ASSERT_EQ(list.getFirst(), list.getLast());
    ASSERT_EQ(list.length(), 1);
    ASSERT_NE(list.getFirst(), nullptr);
    ASSERT_NE(list.getLast(), nullptr);
    ASSERT_EQ(list.getFirst()->data, 1);
    ASSERT_EQ(list.getLast()->data, 1);

    list.pushBack(2);

    ASSERT_EQ(list.length(), 2);
    ASSERT_NE(list.getFirst(), list.getLast());
    ASSERT_EQ(list.getFirst()->data, 1);
    ASSERT_EQ(list.getLast()->data, 2);

}

TEST(LIST_TEST, LinkedList_GetAt) {

    List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);

    for(int i = 1; i <= list.length(); i++) {

        ASSERT_EQ(list.getAt(i)->data, i);

    }

    ASSERT_EQ(list.getAt(120), nullptr);

}

TEST(LIST_TEST, LinkedList_CopyConstruct) {

    List<int> toBeCopied;
    toBeCopied.pushBack(12);
    toBeCopied.pushBack(11);
    toBeCopied.pushBack(13);
    toBeCopied.pushBack(14);
    List<int> copy(toBeCopied);

    ASSERT_EQ(toBeCopied.length(), copy.length());

    Node<int>* copyIter = copy.getFirst();
    Node<int>* toBeCopiedIter = toBeCopied.getFirst();

    for(;toBeCopiedIter; copyIter = copyIter->next, toBeCopiedIter = toBeCopiedIter->next) {

        ASSERT_EQ(copyIter->data, toBeCopiedIter->data);
        ASSERT_NE(copyIter, toBeCopiedIter);

    }

}

TEST(HASHMAP_TEST, HashMap_Set_Get) {

    HashMap<int> newMap;

    String s1 = "Nazwa1";
    String s2 = "Nazwa2";
    String s4 = "Nazwa2";
    String s3 = "Unregistered Key";

    newMap.set(s1, 12);
    newMap.set(s2, 145);
    newMap.set(s4, 11);

    ASSERT_EQ(*newMap.get(s1), 12);
    ASSERT_EQ(*newMap.get(s2), 11);
    //ASSERT_EQ(newMap.get(s3), -1);
    ASSERT_EQ(newMap.collisionCount(), 0);
    ASSERT_EQ(newMap.getCount(), 2);


}

TEST(HASHMAP_TEST, HashMap_Collisions) {

    HashMap<int> newMap;

    newMap.set("START", 35);
    newMap.set("KK", 70);
    newMap.set("WAYPOINT1", 15);
    newMap.set("WAYPOINT2", 14);
    newMap.set("WAYPOINT3", 13);
    newMap.set("KONIEC", 56);

    ASSERT_EQ(*newMap.get("START"), 35);
    ASSERT_EQ(*newMap.get("KK"), 70);
    ASSERT_EQ(*newMap.get("WAYPOINT1"), 15);
    ASSERT_EQ(*newMap.get("WAYPOINT2"), 14);
    ASSERT_EQ(*newMap.get("WAYPOINT3"), 13);
    ASSERT_EQ(*newMap.get("KONIEC"), 56);

}

TEST(VECTOR_TEST, Vector_Init) {

    Vector<int> vec1(2);

    ASSERT_EQ(vec1.capacity(), 2);
    ASSERT_EQ(vec1.size(), 0);

    Vector<int> vec2;

    ASSERT_EQ(vec2.capacity(), 0);
    ASSERT_EQ(vec2.size(), 0);
    ASSERT_EQ(vec2.getBuffer(), nullptr);

}

TEST(VECTOR_TEST, Vector_PushBack) {

    Vector<int> vec1;

    for(int i = 0; i < 100; i++) {

        vec1.pushBack(i);
        ASSERT_EQ(vec1[i], i);

    }
}
