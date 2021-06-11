//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     LENKA SOKOVA <xsokov01@stud.fit.vutbr.cz>
// $Date:       $2021-03-10
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author LENKA SOKOVA
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = { 39, 8, -17, 38, 104, -79, 33, -38, 106, 47, -86, 33, 0, 62 };

        for(auto value : values)
            tree.InsertNode(value);
    }

    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:

    BinaryTree tree1;
    BinaryTree tree2;

    virtual void SetUp(){
        int values[] = { 39, 8, 17, 38, 104, 79, 33, 38, 106, 47, 86, 41, 62 };

        for(auto value : values)
            tree1.InsertNode(value);
    }
};

TEST_F(EmptyTree, InsertNode){
    std::vector<int> values = { 10, 5, 4, 7, 8, 90, -23, 100, 54, 32, 45, 232, -5 , 0 };

    for(auto value : values){
        auto result = tree.InsertNode(value);
        EXPECT_TRUE(result.first);
        EXPECT_EQ(result.second->key, value);
    }

    for(auto value : values){
        auto result1 = tree.InsertNode(value);
        EXPECT_FALSE(result1.first);
        EXPECT_EQ(result1.second->key, value);
    }
}

TEST_F(EmptyTree, DeleteNode){
    int values [] = { 10, 5, 4, 7, 8, 90, -23, 100, 54, 32, 45, 232, -5 , 0 };

    for (auto value : values){
        EXPECT_FALSE(tree.DeleteNode(value));
    }
}

TEST_F(EmptyTree, FindNode){
    int values [] = { 10, 5, 4, 7, 8, 90, -23, 100, 54, 32, 45, 232, -5 , 0 };

    for (auto value : values){
        EXPECT_EQ(tree.FindNode(value), nullptr);
    }
}

TEST_F(NonEmptyTree, InsertNode) {
    int importedValues[] = { 39, 8, -17, 38, 104, -79, 33, -38, 106, 47, -86, 0, 62 };
    int NotImportedValues[] = {7, 10, -100, 54, 23, 45 };

    for (auto value : importedValues) {

        auto result = tree.InsertNode(value);
        EXPECT_FALSE(result.first);
        EXPECT_EQ(result.second->key, value);
    }

    for (auto value : NotImportedValues) {
        auto result = tree.InsertNode(value);
        EXPECT_TRUE(result.first);
        EXPECT_EQ(result.second->key, value);
    }
}

TEST_F(NonEmptyTree, DeleteNode){

    int importedValues[] = { 39, 8, -17, 38, 104, -79, 33, -38, 106, 47, -86, 0, 62 };
    int NotImportedValues[] = { 7, 10, -100, 54, 23, 45 };

    for(auto value : NotImportedValues){
        EXPECT_FALSE(tree.DeleteNode(value));
    }

    for (auto value : importedValues){
        EXPECT_TRUE(tree.DeleteNode(value));
    }
}

TEST_F(NonEmptyTree, FindNode){
    int importedValues[] = { 39, 8, -17, 38, 104, -79, 33, -38, 106, 47, -86, 0, 62 };
    int NotImportedValues[] = { 7, 10, -100, 54, 23, 45 };

    for (auto value : NotImportedValues){
        EXPECT_EQ(tree.FindNode(value), nullptr);
    }

    for (auto value : importedValues){
        EXPECT_EQ(tree.FindNode(value)->key, value);
    }
}

TEST_F(TreeAxioms, Axiom1){
    std::vector<Node_t *> LeafNodesTree1 {};
    tree1.GetLeafNodes(LeafNodesTree1);

    for(auto node : LeafNodesTree1){
        EXPECT_EQ(node->color, BLACK);
    }

    std::vector<Node_t *> LeafNodesTree2 {};
    tree2.GetLeafNodes(LeafNodesTree2);
    for(auto node : LeafNodesTree2){
        EXPECT_EQ(node->color, BLACK);
    }

}

TEST_F(TreeAxioms, Axiom2) {
    std::vector<Node_t *> NonLeafNodesTree1{};
    tree1.GetNonLeafNodes(NonLeafNodesTree1);

    std::vector<Node_t *> NonLeafNodesTree2{};
    tree2.GetNonLeafNodes(NonLeafNodesTree1);

    std::vector<Node_t *> AllNodesTree1{};
    tree1.GetAllNodes(AllNodesTree1);

    std::vector<Node_t *> AllNodesTree2{};
    tree2.GetAllNodes(AllNodesTree1);

    for (auto node : NonLeafNodesTree1) {
        if (node->color == RED) {
            if (node->pLeft != nullptr)
                EXPECT_EQ(node->pLeft->color, BLACK);
            if (node->pRight != nullptr)
                EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

    for (auto node : NonLeafNodesTree2) {
        if (node->color == RED) {
            if (node->pLeft != nullptr)
                EXPECT_EQ(node->pLeft->color, BLACK);
            if (node->pRight != nullptr)
                EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

    for (auto node : AllNodesTree1) {
        if (node->color == RED) {
            if (node->pLeft != nullptr)
                EXPECT_EQ(node->pLeft->color, BLACK);
            if (node->pRight != nullptr)
                EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

    for (auto node : AllNodesTree2) {
        if (node->color == RED) {
            if (node->pLeft != nullptr)
                EXPECT_EQ(node->pLeft->color, BLACK);
            if (node->pRight != nullptr)
                EXPECT_EQ(node->pRight->color, BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3){
    std::vector<Node_t *> LeafNodesTree1 {};
    tree1.GetLeafNodes(LeafNodesTree1);

    int previousNode = -1;
    int cntBlackNode = 0;

    for (auto node : LeafNodesTree1){

        while(node != tree1.GetRoot()){
            if(node->color == BinaryTree::BLACK){
                cntBlackNode += 1;
            }

            node = node->pParent;
        }

        if (previousNode != -1){
            EXPECT_EQ(cntBlackNode, previousNode);
        }

        //porovna s predchadzajucou hodnotou
        previousNode = cntBlackNode;
        cntBlackNode = 0;
    }
}

/*** Konec souboru black_box_tests.cpp ***/
