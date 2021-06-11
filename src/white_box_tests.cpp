//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     LENKA SOKOVA <xsokov01@stud.fit.vutbr.cz>
// $Date:       $2021-03-10
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author LENKA SOKOVA
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class EmptyMatrix : public ::testing::Test{
protected:
    Matrix matrix;
};

class NonEmptyMatrix : public ::testing::Test{
protected:

    Matrix m2x2;
    Matrix m3x3_1;
    Matrix m3x3_2;
    Matrix m5x5;
    Matrix m2x3;
    Matrix m2x5;
    Matrix m1x4;
    Matrix m6x6;

    virtual void SetUp(){
        m2x2 = getMatrix2x2();
        m3x3_1 = getMatrix3x3_1();
        m3x3_2 = getMatrix3x3_2();
        m5x5 = getMatrix5x5();
        m2x3 = getMatrix2x3();
        m2x5 = getMatrix2x5();
        m1x4 = getMatrix1x4();
        m6x6 = getMatrix6x6();
    }

    Matrix getMatrix2x2(){
        Matrix mat = Matrix(2, 2);
        mat.set(std::vector<std::vector<double>> {
                {1,2},
                {3,4}
        });

        return mat;
    }
    Matrix getMatrix3x3_1(){
        Matrix mat = Matrix(3, 3);
        mat.set(std::vector<std::vector<double>> {
                {1,2,3},
                {4,5,6},
                {7,8,9}
        });

        return mat;
    };

    Matrix getMatrix3x3_2(){
        Matrix mat = Matrix(3, 3);
        mat.set(std::vector<std::vector<double>> {
                {1.3,-2,3.8},
                {400,-500,6.9},
                {70.765,8.45,-9}
        });

        return mat;
    }

    Matrix getMatrix5x5(){
        Matrix mat = Matrix(5, 5);
        mat.set(std::vector<std::vector<double>> {
                {1.3,-2,3.8, 8, 9},
                {400,-500,6.9, 7, -6},
                {70.765,8.45,-9, -98, 65},
                {45.7, -98, -54, 1, 0},
                {98.5, 34, 23.5, 12, 9}
        });

        return mat;
    }

    Matrix getMatrix2x3(){
        Matrix mat = Matrix(2, 3);
        mat.set(std::vector<std::vector<double>> {
                {1, 2, 3},
                {4, 5, 6}
        });

        return mat;
    }

    Matrix getMatrix2x5(){
        Matrix mat = Matrix(2, 5);
        mat.set(std::vector<std::vector<double>> {
                {1.3,-2,3.8, 8, 9},
                {400,-500,6.9, 7, -6},
        });

        return mat;
    }

    Matrix getMatrix1x4(){
        Matrix mat = Matrix(1, 4);
        mat.set(std::vector<std::vector<double>> {
                {1.3,-2,3.8, 8},
        });

        return mat;
    }

    Matrix getMatrix6x6(){
        Matrix mat(6, 6);
        mat.set(std::vector<std::vector<double>> {
                {1, 2, 3, 4, 5, 6},
                {11, 12, 13, 14, 15, 16},
                {7, 8, 9, 10, 11, 12},
                {0, 2, 4, 6, 8, 10},
                {3, 6, 9, 12, 18, 21},
                {4, 8, 12, 16, 100, 24}
        });

        return mat;
    }


};


TEST_F(EmptyMatrix, MatrixConstructor){

    EXPECT_ANY_THROW(Matrix(1, 0));
    EXPECT_ANY_THROW(Matrix(0, 0));
    EXPECT_ANY_THROW(Matrix(0, 1));
    EXPECT_ANY_THROW(Matrix(-10,3));
    EXPECT_ANY_THROW(Matrix(4, -34));
    EXPECT_ANY_THROW(Matrix(-45, -34));
    EXPECT_NO_THROW(Matrix(1, 1));
    EXPECT_NO_THROW(Matrix(3, 7));
    EXPECT_NO_THROW(Matrix());

    EXPECT_EQ(matrix.get(0,0), 0);
}

TEST_F(EmptyMatrix, SetValue){

    EXPECT_FALSE(matrix.set(5, 6, 7));
    EXPECT_FALSE(matrix.set(-1, 0, 3));
    EXPECT_FALSE(matrix.set(0, -1, 3));
    EXPECT_FALSE(matrix.set(-3, -3, -3));
    EXPECT_FALSE(matrix.set(1,1,1));

    EXPECT_TRUE(matrix.set(0, 0, 1));
    EXPECT_EQ(matrix.get(0,0), 1);
}

TEST_F(EmptyMatrix, setValues){

    EXPECT_ANY_THROW(matrix.set(std::vector<std::vector< double > >(-1, std::vector<double>(1, 5))));

    EXPECT_FALSE(matrix.set(std::vector<std::vector< double > >(1, std::vector<double>(3, 5))));
    EXPECT_FALSE(matrix.set(std::vector<std::vector< double > >(3, std::vector<double>(1, 5))));
    EXPECT_FALSE(matrix.set(std::vector<std::vector< double > > {{21, 64.5, -21, 269.25, 225, 195}}));
    EXPECT_FALSE(matrix.set(std::vector<std::vector< double > > {{}}));

    EXPECT_TRUE(matrix.set(std::vector<std::vector< double > >(1, std::vector<double>(1, 5))));
    EXPECT_EQ(matrix.get(0,0), 5);
}

TEST_F(EmptyMatrix, getValue){
    EXPECT_ANY_THROW(matrix.get(3,0));
    EXPECT_ANY_THROW(matrix.get(0,3));
    EXPECT_ANY_THROW(matrix.get(-1,0));
    EXPECT_ANY_THROW(matrix.get(0,-1));

    EXPECT_NO_THROW(matrix.get(0,0));

    EXPECT_EQ(matrix.get(0,0), 0);
}

TEST_F(EmptyMatrix, compareMatrix){
    EXPECT_ANY_THROW(matrix == (Matrix(1, 3)));
    EXPECT_ANY_THROW(matrix == (Matrix(3, 1)));

    Matrix mat{1, 1};
    mat.set(0, 0, 5);

    EXPECT_FALSE(matrix ==(mat));

    mat.set(0, 0, 0);
    EXPECT_TRUE(matrix ==(mat));
}

TEST_F(EmptyMatrix, countMatrix) {
    EXPECT_ANY_THROW(matrix + Matrix(1, 3));
    EXPECT_ANY_THROW(matrix +Matrix(3, 1));

    Matrix mat{1, 1};
    mat.set(0, 0, 5);
    EXPECT_TRUE(mat == (matrix +(mat)));

    Matrix matCountResult{1, 1};
    matCountResult.set(0, 0, 50);
    matrix.set(0, 0, 45);
    EXPECT_TRUE(matCountResult ==(matrix +(mat)));
}

TEST_F(EmptyMatrix, multiplyMatrix){
    EXPECT_ANY_THROW(matrix *(Matrix(3, 1)));

    Matrix matMultiplyResult{1, 6};
    matMultiplyResult.set(std::vector<std::vector< double > >(1, std::vector<double>(6, 0)));

    Matrix matMultiply{1, 6};
    matMultiply.set(std::vector<std::vector<double>> {
            {7, 21.5, -7, 89.75, 75, 65},
    });

    EXPECT_TRUE(matMultiplyResult ==(matrix *(matMultiply)));

    matrix.set(0, 0, 3);
    matMultiplyResult.set(std::vector<std::vector< double > > {
            {21, 64.5, -21, 269.25, 225, 195}
    });
    EXPECT_TRUE(matMultiplyResult ==(matrix *(matMultiply)));
}

TEST_F(EmptyMatrix, multiplyMatrixByValue){
    EXPECT_TRUE(matrix *(5) ==(matrix));
    matrix.set(0, 0, 5);

    Matrix matMultiplyResult(1, 1);
    matMultiplyResult.set(std::vector<std::vector< double > > {
            {25}
    });

    EXPECT_TRUE(matMultiplyResult ==(matrix *(5)));
}

TEST_F(EmptyMatrix, solveEquation){
    EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {1, 2, 3, 4, 5}));

    Matrix mat{3, 1};
    mat.set(std::vector<std::vector< double > > {
            {1},
            {2},
            {3}
    });

    EXPECT_ANY_THROW(mat.solveEquation({1,2,3}));
    EXPECT_ANY_THROW(matrix.solveEquation({1}));
    matrix.set(0, 0, 5);


    EXPECT_TRUE(matrix.solveEquation(std::vector<double> {5}) == (std::vector<double> {1}));
}


TEST_F(NonEmptyMatrix, setValue){
    EXPECT_FALSE(m2x2.set(5, 5, 7));
    EXPECT_FALSE(m2x2.set(-1, 0, 3));
    EXPECT_FALSE(m1x4.set(3, 0, 3));
    EXPECT_FALSE(m2x5.set(4, 1, -3));

    EXPECT_TRUE(m3x3_1.set(0, 0, 0));
    EXPECT_TRUE(m5x5.set(4,4, 4));

    EXPECT_EQ(m3x3_1.get(0,0), 0);
    EXPECT_EQ(m5x5.get(4,4),4);
}


TEST_F(NonEmptyMatrix, setValues){
    EXPECT_FALSE(m2x2.set(std::vector<std::vector< double > > {{21, 64.5, -21, 269.25, 225, 195}}));
    EXPECT_FALSE(m3x3_1.set(std::vector<std::vector< double > > {{1, 2}, {3, 4}, {5, 6}}));
    EXPECT_FALSE(m3x3_1.set(std::vector<std::vector< double > > {{1, 2, 3}, {4, 5, 6}}));

    EXPECT_TRUE(m3x3_2.set(std::vector<std::vector< double > > {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}));
    EXPECT_EQ(m3x3_2.get(0,0), 0);
    EXPECT_EQ(m3x3_2.get(2,2), 8);

    EXPECT_TRUE(m1x4.set(std::vector<std::vector< double > > {{0.5, 0.75, -2, 10000}}));
    EXPECT_EQ(m1x4.get(0,0), 0.5);
    EXPECT_EQ(m1x4.get(0,3), 10000);
}

TEST_F(NonEmptyMatrix, getValue){
    EXPECT_ANY_THROW(m2x2.get(1,3));
    EXPECT_ANY_THROW(m2x5.get(4,1));
    EXPECT_ANY_THROW(m5x5.get(-500, 500));

    EXPECT_NO_THROW(m2x5.get(1,4));
    EXPECT_EQ(m2x5.get(1,4), -6);

    EXPECT_NO_THROW(m3x3_1.get(0,0));
    EXPECT_EQ(m3x3_1.get(0,0), 1);
}

TEST_F(NonEmptyMatrix, compareMatrix){
    EXPECT_ANY_THROW(m1x4 == m2x5);
    EXPECT_ANY_THROW(m1x4 == m3x3_1);
    EXPECT_ANY_THROW(m3x3_1 == m5x5);

    EXPECT_FALSE(m3x3_1 == m3x3_2);
    EXPECT_FALSE(m3x3_2 == m3x3_1);
    EXPECT_FALSE(m1x4 == Matrix(1,4));

    EXPECT_TRUE(Matrix() == Matrix());
    EXPECT_TRUE(m5x5 == m5x5);

    Matrix mat = getMatrix2x5();
    EXPECT_TRUE(mat == m2x5);
}

TEST_F(NonEmptyMatrix, countMatrix){
    EXPECT_ANY_THROW(m1x4 + m2x5);
    EXPECT_ANY_THROW(m1x4 + m3x3_1);
    EXPECT_ANY_THROW(m3x3_1 + m5x5);

    EXPECT_NO_THROW(Matrix() + Matrix());
    EXPECT_NO_THROW(m3x3_1 + m3x3_2);

    EXPECT_FALSE(m3x3_1 + m3x3_2 == m3x3_1);
    EXPECT_FALSE(m1x4 + m1x4 == m1x4);

    Matrix mat1(2,2);
    mat1.set(std::vector<std::vector< double > > {{2, 4}, {6, 9}});
    EXPECT_FALSE(m2x2 + m2x2 == mat1);


    mat1.set(std::vector<std::vector< double > > {{2, 4}, {6, 8}});
    EXPECT_TRUE(m2x2 + m2x2 == mat1);

    Matrix mat2(1,4);
    mat2.set(std::vector<std::vector< double > > {{2.6, -4, 7.6, 16}});
    EXPECT_TRUE(m1x4 + m1x4 == mat2);
}

TEST_F(NonEmptyMatrix, multipleMatrix){
    EXPECT_ANY_THROW(m2x5 * m2x2);
    EXPECT_ANY_THROW(m1x4 * m3x3_1);
    EXPECT_ANY_THROW(m5x5 * m2x5);

    EXPECT_NO_THROW(m2x5 * m5x5);
    EXPECT_NO_THROW(m2x2 * m2x5);
    EXPECT_NO_THROW(m3x3_1 * m3x3_2);

    EXPECT_FALSE(m3x3_1 * m3x3_2 == m3x3_2);
    EXPECT_FALSE(m2x2 * m2x5 == m2x5);

    EXPECT_TRUE(Matrix(1,4) * Matrix(4,1) == Matrix());

    Matrix mat1(2,5);
    mat1.set(std::vector<std::vector< double > > {{801.3, -1002, 17.6, 22, -3}, {1603.9, -2006, 39, 52, 3}});
    EXPECT_TRUE(m2x2 * m2x5 == mat1);

    Matrix mat2(2, 3);
    mat2.set(std::vector<std::vector< double > > {
            {9, 12, 15},
            {19, 26, 33}
    });
    EXPECT_TRUE(m2x2 * m2x3 == mat2);
}

TEST_F(NonEmptyMatrix, multipleMatrixByConst){

    EXPECT_FALSE(m5x5 == m5x5 * 2);

    EXPECT_TRUE(m2x2 + m2x2 == m2x2 * 2);
    EXPECT_TRUE(m1x4 * 4 == m1x4 + m1x4 + m1x4 + m1x4);
    EXPECT_TRUE(m5x5 * 0 == Matrix(5, 5) * 5);

    Matrix mat1(2, 3);
    mat1.set(std::vector<std::vector< double > > {
            {3, 6, 9},
            {12, 15, 18}
    });

    EXPECT_TRUE(m2x3 * 3 == mat1);
}

TEST_F(NonEmptyMatrix, solveEquation){
    std::vector<double> r1 = {1};
    std::vector<double> r2 = {1,2};
    std::vector<double> r3 = {1,2,3};
    std::vector<double> r4 = {1,2,3,4};
    std::vector<double> r5 = {1,2,3,4,5};
    std::vector<double> r6 = {1,1,1,1,1,1};

    EXPECT_ANY_THROW(m3x3_1.solveEquation(r1));
    EXPECT_ANY_THROW(m1x4.solveEquation(r2));
    EXPECT_ANY_THROW(m5x5.solveEquation(r3));

    EXPECT_ANY_THROW(m2x3.solveEquation(r3));
    EXPECT_ANY_THROW(m1x4.solveEquation(r4));

    EXPECT_ANY_THROW(Matrix().solveEquation(r1));
    EXPECT_ANY_THROW(Matrix(3,3).solveEquation((r3)));
    EXPECT_ANY_THROW(m3x3_1.solveEquation(r3));
    EXPECT_ANY_THROW(m6x6.solveEquation((r6)));

    EXPECT_FALSE(m3x3_2.solveEquation(r3) == r3);


    std::vector<double> r2x2 = {1, 1};
    EXPECT_TRUE(m2x2.solveEquation({3,7}) == r2x2);

    Matrix mat(4, 4);
    mat.set(std::vector<std::vector< double > > {
        {1, 2, 3, -4},
        {5, 6, 7, 8},
        {9, -10, 11, 12},
        {13, 14, 15, 16}});

    std::vector<double> r4x4 = {1, 1, 1, 1};
    EXPECT_TRUE(mat.solveEquation({2, 26, 22, 58}) == r4x4);
}

TEST_F(NonEmptyMatrix, transposeMatrix){
    EXPECT_FALSE(m3x3_2.transpose() == m3x3_2);

    Matrix mat(2, 2);
    mat.set(std::vector<std::vector< double > > {{1, 3}, {2, 4}});

    EXPECT_TRUE(m2x2.transpose() == mat);
    EXPECT_TRUE(Matrix().transpose() == Matrix().transpose());

    Matrix mat1(3, 3);
    mat1.set(std::vector<std::vector< double > > {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    EXPECT_TRUE(mat1.transpose() == mat1);
}

TEST_F(NonEmptyMatrix, inverseMatrix){
    Matrix inv2x2(2,2);
    inv2x2.set(std::vector<std::vector< double > > {
        {-2, 1},
        {1.5, -0.5}});

    Matrix m3x3(3, 3);
    m3x3.set(std::vector<std::vector< double > > {
            {1, 2, -3},
            {4, -5, 6},
            {7, 8, 9}});

    EXPECT_ANY_THROW(m1x4.inverse());
    EXPECT_ANY_THROW(m5x5.inverse());
    EXPECT_ANY_THROW(m3x3_1.inverse());

    EXPECT_NO_THROW(m3x3.inverse());

    EXPECT_TRUE(m2x2.inverse() == inv2x2);
}


/*** Konec souboru white_box_tests.cpp ***/
