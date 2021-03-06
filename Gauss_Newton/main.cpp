#include <iostream>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

/*
 * 程序说明：为了验证Gauss-Newton法寻找梯度增量的效果，我们假设已知真实的参数（在实际应用中我们要做的就是估计、优化这些参数）
 * 1.先利用真实参数生成真实的x,y数据
 * 2.将估计的参数代入Gauss-Newton模型进行优化
 * 3.优化后的结果与真实参数进行比较
 */
int main(int argc, char **argv) {
    double ar = 1.0, br = 2.0, cr = 1.0;         // 真实参数值
    double ae = 2.0, be = -1.0, ce = 5.0;        // 估计参数值
    int N = 100;                                 // 数据点
    double w_sigma = 1.0;                        // 噪声Sigma值
    cv::RNG rng;                                 // OpenCV随机数产生器

    vector<double> x_data, y_data;               // 数据
    for (int i = 0; i < N; i++) {
        double x = i / 100.0;
        x_data.push_back(x);
        y_data.push_back(exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma));
    }

    /**************************开始Gauss-Newton迭代****************************/
    int iterations = 100;    // 迭代次数
    double cost = 0, lastCost = 0;  // 本次迭代的cost和上一次迭代的cost

    for (int iter = 0; iter < iterations; iter++) {

        Matrix3d H = Matrix3d::Zero();             // Hessian = J^T J in Gauss-Newton
        Vector3d b = Vector3d::Zero();             // bias
        cost = 0;

        for (int i = 0; i < N; i++) {
            double xi = x_data[i], yi = y_data[i];  // 第i个数据点
            
            //========注意这里不是error ^ 2，Gauss-Newton明确指出是对error进行一阶泰勒展开，可以试着取消以下注释，进行计算，优化结果会比较差=======
            //double error = ( yi - exp(ae * xi * xi + be * xi + ce) ) * ( yi - exp(ae * xi * xi + be * xi + ce) );
            //Vector3d J; // 雅可比矩阵
            //J[0] = -2 * (yi - exp(ae * xi * xi + be * xi + ce)) * exp(ae * xi * xi + be * xi + ce) * xi * xi;  // de/da
            //J[1] = -2 * (yi - exp(ae * xi * xi + be * xi + ce)) * exp(ae * xi * xi + be * xi + ce) * xi;       // de/db
            //J[2] = -2 * (yi - exp(ae * xi * xi + be * xi + ce)) * exp(ae * xi * xi + be * xi + ce) ;           // de/dc
            //============================================================================================================
            
            double error = yi - exp(ae * xi * xi + be * xi + ce);
            Vector3d J; // 雅可比矩阵，实值标量函数对行向量求偏导，结果也为行向量，所以在这是雅可比矩阵是3维向量。
            J[0] = -exp(ae * xi * xi + be * xi + ce) * xi * xi;  // d(error)/d(ae),公式可看下图。
            J[1] = -exp(ae * xi * xi + be * xi + ce) * xi;       // d(error)/d(be)
            J[2] = -exp(ae * xi * xi + be * xi + ce) ;           // d(error)/d(ce)

            H += J * J.transpose(); // GN近似的H
            b += -error * J;
    
            cost += error * error;
	    
        }

        // 求解线性方程 Hx=b，建议用ldlt
        Vector3d dx;
	dx = H.ldlt().solve(b);

	//true if arg is a NaN(not a number), false otherwise 
        if (isnan(dx[0])) {
            cout << "result is nan!" << endl;
            break;
        }

        if (iter > 0 && cost > lastCost) {
            // 误差增长了，说明近似的不够好
            cout << "cost: " << cost << ", last cost: " << lastCost << endl;
            break;
        }

        // 因为要寻找使error最小的ae,be,ce，所以要不断更新ae,be,ce估计值实现向最优的ae,be,ce值的逼近
        ae += dx[0];
        be += dx[1];
        ce += dx[2];

        lastCost = cost;

        cout << "total cost: " << cost << endl;
    }

    cout << "estimated abc = " << ae << ", " << be << ", " << ce << endl;
    return 0;
}