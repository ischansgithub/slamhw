#include <iostream>
using namespace std;
#include <ctime>
// Eigen 部分
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆，特征值等）
#include <Eigen/Dense>
#include <Eigen/QR>
#include<Eigen/Cholesky>

#define MATRIX_SIZE 50

/****************************
* 本程序演示了 Eigen 基本类型的使用
****************************/

int main( int argc, char** argv )
{
    Eigen::Matrix<double, 100, 100> matrix_A;
    matrix_A = Eigen::MatrixXd::Random(100, 100);
    
    Eigen::Matrix<double, 100, 1> vector_b;
    vector_b = Eigen::MatrixXd::Random(100, 1);
    
    Eigen::Matrix<double, 100, 1> x_qr;
    Eigen::Matrix<double, 100, 1> x_ldlt;
    
    cout << "-------------------QR分解---------------------" << endl;
    clock_t time_stt = clock(); // 计时
    x_qr = matrix_A.colPivHouseholderQr().solve(vector_b);
    cout << x_qr << endl;
    cout <<"time use in Qr decomposition is " <<1000*  (clock() - time_stt)/(double)CLOCKS_PER_SEC <<"ms" << endl;
    
    cout << "-------------------IDLT分解---------------------" << endl;
    time_stt = clock();
    x_ldlt = matrix_A.ldlt().solve(vector_b);
    cout << x_ldlt << endl;
    cout <<"time use in Qr decomposition is " <<1000*  (clock() - time_stt)/(double)CLOCKS_PER_SEC <<"ms" << endl;

    return 0;
}
