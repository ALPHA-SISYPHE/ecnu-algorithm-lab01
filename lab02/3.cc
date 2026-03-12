#include <iostream>
#include <vector>

using namespace std;
using Matrix = std::vector<std::vector<int>>;

Matrix sub(const Matrix &mat1, const Matrix &mat2)
{
    int n = mat1.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = mat1[i][j] - mat2[i][j];
        }
    }

    return C;
}

Matrix add(const Matrix &mat1, const Matrix &mat2)
{
    int n = mat1.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    return C;
}

Matrix strassen(const Matrix &mat1, const Matrix &mat2)
{
    int n = mat1.size();
    //添加小数据量朴素乘法优化代码
    if (n <= 64) {
        Matrix C(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return C;
    }
    // 开始分割矩阵
    int half = n / 2;
    Matrix A11(half, vector<int>(half));
    Matrix A12(half, vector<int>(half));
    Matrix A21(half, vector<int>(half));
    Matrix A22(half, vector<int>(half));

    Matrix B11(half, vector<int>(half));
    Matrix B12(half, vector<int>(half));
    Matrix B21(half, vector<int>(half));
    Matrix B22(half, vector<int>(half));

    // 分割完毕，开始赋值
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            A11[i][j] = mat1[i][j];
            A12[i][j] = mat1[i][j + half];
            A21[i][j] = mat1[i + half][j];
            A22[i][j] = mat1[i + half][j + half];

            B11[i][j] = mat2[i][j];
            B12[i][j] = mat2[i][j + half];
            B21[i][j] = mat2[i + half][j];
            B22[i][j] = mat2[i + half][j + half];
        }
    }

    // 赋值完毕，开始计算
    Matrix temp,temp0;

    // 递归计算7个P
    temp = sub(B12, B22);
    Matrix P1 = strassen(A11, temp);

    temp = add(A11, A12);
    Matrix P2 = strassen(temp, B22);
    
    temp = add(A21, A22);
    Matrix P3 = strassen(temp, B11);

    temp = sub(B21, B11);
    Matrix P4 = strassen(A22, temp);

    temp = add(A11, A22);
    temp0 = add(B11, B22);
    Matrix P5 = strassen(temp, temp0);

    temp =sub(A12, A22);
    temp0 = add(B21, B22);
    Matrix P6 = strassen(temp, temp0);

    // P7 = (A11 - A21) × (B11 + B12)
    temp = sub(A11, A21);
    temp0 = add(B11, B12);
    Matrix P7 = strassen(temp, temp0);

    // 输出4个C
    Matrix C11 = add(sub(add(P5, P4), P2), P6);
    Matrix C12 = add(P1, P2);
    Matrix C21 = add(P3, P4);
    Matrix C22 = sub(add(P5, P1), add(P3, P7));

    // 最终合并
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < half; ++i)
    {
        for (int j = 0; j < half; ++j)
        {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

int main()
{
    int n;
    cin >> n;
    Matrix mat1(n, vector<int>(n));
    Matrix mat2(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mat1[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mat2[i][j];
        }
    }

    Matrix ans = strassen(mat1, mat2);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != n - 1)
                cout << ans[i][j] << ' ';
            else
                cout << ans[i][j];
        }
        if (i != n - 1)
            cout << endl;
    }
}