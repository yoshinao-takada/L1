# Variables and Objective Function
The variable is a four dimensional vector, 
$\begin{bmatrix}x_0 & x_1 & x_2 & x_3\end{bmatrix}$. The vector elements are mapped to elements of
a 2x2 matrix,
$$\text{M}_0 = \begin{bmatrix}
x_0 & x_1 \\ x_2 & x_3
\end{bmatrix}$$
Considering constant parameters $C_0$ and $C_1$, which are added to the diagonal elements of the 
matrix above to make a matrix
$$\text{M}_1 = \begin{bmatrix}
x_0 + C_0 & x_1 \\ x_2 & x_3 + C_1
\end{bmatrix}$$
dependent variable is an eight dimensional vector. Its first half is the elements of ${\text{M}_1}^2$.
$$\text{M}_2 = {\text{M}_1}^2 =\begin{bmatrix}
(x_0+C_0)^2+x_1x_2 & x_1(x_0+x_3+C_0+c_1)\\
x_2(x_0+x_3+C_0+c_1) & x_1x_2+(x_3+C_1)^2
\end{bmatrix}$$
The last half is the elements of ${\text{M}_1}^3$.
$$\text{M}_3 = {\text{M}_1}^3 = \begin{bmatrix}
(x_0+C_0)^2+x_1x_2 & x_1(x_0+x_3+C_0+c_1)\\
x_2(x_0+x_3+C_0+c_1) & x_1x_2+(x_3+C_1)^2
\end{bmatrix}\begin{bmatrix}
x_0 + C_0 & x_1 \\ x_2 & x_3 + C_1
\end{bmatrix}$$
$$\begin{equation}
\frac{\partial}{\partial{x_0}}{\text{M}_2} =
\text{M}_1\begin{bmatrix}1 & 0\\0 & 0\end{bmatrix}+
\begin{bmatrix}1 & 0\\0 & 0\end{bmatrix}\text{M}_1
=\begin{bmatrix}2(x_0+C_0) & x_1\\x_2 & 0\end{bmatrix}
\end{equation}$$
$$\begin{equation}
\frac{\partial}{\partial{x_1}}{\text{M}_2}=
\text{M}_1\begin{bmatrix}0 & 1\\0 & 0\end{bmatrix}+
\begin{bmatrix}0 & 1\\0 & 0\end{bmatrix}\text{M}_1 =
\begin{bmatrix}x_2 & x_0+x_3+C_0+C_1\\0 & x_2\end{bmatrix}
\end{equation}$$
$$\begin{equation}
\frac{\partial}{\partial{x_2}}\text{M}_2 =
\text{M}_1\begin{bmatrix}0 & 0\\1 & 0\end{bmatrix}+
\begin{bmatrix}0 & 0\\1 & 0\end{bmatrix}\text{M}_1=
\begin{bmatrix}x_1 & 0\\x_0+x_3+C_0+C_1 & x_1\end{bmatrix}
\end{equation}$$
$$\begin{equation}
\frac{\partial}{\partial{x_3}}\text{M}_2 = 
\text{M}_1\begin{bmatrix}0 & 0\\0&1\end{bmatrix} +
\begin{bmatrix}0 & 0\\0&1\end{bmatrix}\text{M}_1 =
\begin{bmatrix}0 & x_1\\x_2 & 2(x_3+C_1)\end{bmatrix}
\end{equation}$$
$$
\frac{\partial}{\partial{x_0}}\text{M}_3=
\begin{bmatrix}1&0\\0&0\end{bmatrix}\text{M}_2+
{\text{M}_1}\begin{bmatrix}1&0\\0&0\end{bmatrix}\text{M}_1+
{\text{M}_2}\begin{bmatrix}1&0\\0&0\end{bmatrix}
$$
$$
\begin{bmatrix}(x_0+C_0)^2+x_1x_2 & x_1(x_0+x_3+C_0+C_1)\\0&0\end{bmatrix} +
$$
$$
\begin{bmatrix}(x_0+C_0)^2&(x_0+C_0)x_1\\x_2(x_0+C_0)&x_1x_2\end{bmatrix} +
$$
$$
\begin{bmatrix}(x_0+C_0)^2+x_1x_2 & 0\\x_2(x_0+x_3+C_0+C_1)&0\end{bmatrix} +
$$
$$\begin{equation}=\begin{bmatrix}
3(x_0+C_0)^2&x_1(2x_0+x_3+2C_0+C_1)\\x_2(2x_0+x_3+2C_0+C_1)&x_1x_2
\end{bmatrix}\end{equation}$$
