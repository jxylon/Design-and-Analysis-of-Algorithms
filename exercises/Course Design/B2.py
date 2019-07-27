import random
from graphics import *
import time

num = []
max_matrix = []


def init_num():
    """
    初始化数塔
    """
    print('请输入n')
    n = input()
    while (not n.isdigit()):
        print('请重新输入')
        n = input()
    n = int(n)
    for i in range(1, n + 1):
        array = []
        array_max = []
        for j in range(i):
            k = random.randint(0, 100)
            array.append(k)
            array_max.append([k, -1])
        num.append(array)
        if (i == n):
            max_matrix.append(array_max)
        else:
            max_matrix.append([])
    return n

def max_num(n):
    # 创建窗口
    max_x0 = 1000
    max_y0 = 800
    win = GraphWin('数塔', max_x0, max_y0)
    # 画原数塔
    x0, x, y = max_x0/2, max_x0/2, 80
    cirlist = []
    textlist = []
    for i in range(len(num)):
        cir_l = []
        text_l = []
        for j in range(len(num[i])):
            cir = Circle(Point(x, y), 30)
            cir_l.append(cir)
            cir.setFill('brown')
            cir.draw(win)
            text = Text(Point(x, y), str(num[i][j]))
            text_l.append(text)
            text.draw(win)
            x += 100
        cirlist.append(cir_l)
        textlist.append(text_l)
        y += 80
        x = x0 - 50
        x0 = x
    # 动态规划算法实现
    for cir in cirlist[-1]:
        cir.setFill('blue')
        time.sleep(0.5)
    n = len(num)
    for i in range(n - 2, -1, -1):
        for j in range(len(num[i])):
            # 比较下一层中左右较大值
            if (max_matrix[i + 1][j][0] > max_matrix[i + 1][j + 1][0]):
                max = max_matrix[i + 1][j][0] + num[i][j]
                max_i = j
            else:
                max = max_matrix[i + 1][j + 1][0] + num[i][j]
                max_i = j + 1
            max_matrix[i].append([max, max_i])
            # 画图
            cirlist[i + 1][j].setFill('green')
            cirlist[i + 1][j + 1].setFill('green')
            cirlist[i][j].setFill('green')
            time.sleep(0.5)
            cirlist[i + 1][max_i].setFill('yellow')
            time.sleep(0.5)
            cirlist[i + 1][j].setFill('white')
            cirlist[i + 1][j + 1].setFill('white')
            cirlist[i][j].setFill('brown')
            textlist[i][j].setText(str(max))
    # 回溯得到路径
    max_i = 0
    best_str = '最大总和为：'
    for i in range(len(max_matrix)):
        # 最大路径设置为黄色
        cirlist[i][max_i].setFill('yellow')
        time.sleep(0.1)
        # 最大路径的结点值
        max_n = num[i][max_i]
        if (i == 0):
            best_str += str(max_matrix[i][max_i][0]) + ',路径：'
        # 下一个最佳结点
        max_i = max_matrix[i][max_i][1]
        best_str += str(max_n)
        if (i != (len(max_matrix) - 1)):
            best_str += '->'
    # 还原数塔图
    for i in range(len(cirlist)):
        for j in range(len(cirlist[i])):
            textlist[i][j].setText(str(num[i][j]))
    # 最佳路径
    text = Text(Point(200, max_y0 - 20), best_str)
    text.draw(win)
    # 点击屏幕关闭
    win.getMouse()
    win.close()


def main():
    n=init_num()
    max_num(n)


if __name__ == '__main__':
    main()
