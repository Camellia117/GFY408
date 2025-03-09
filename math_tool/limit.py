from sympy import symbols, limit, sympify, oo
from sympy.parsing.sympy_parser import parse_expr
# from math_tool.limit import calculate_limit
def finnnn():
    # 输入自变量
    var = input("请输入自变量(例如x): ").strip()
    x = symbols(var)

    # 输入趋向值
    to_raw = input(f"请输入 {var} 趋向的值(例如 0, 5, oo): ").strip().lower
    to = to_raw

    # 输入函数表达式
    expr_str = input(f"输入关于 {var} 的函数表达式: ").strip()
    # 输入趋向的方向 - or +
    # dir = None
    # dir = input(f"输入是从哪个方向趋近 {var}, - or + ").strip()

    result = limit(expr_str, x, to)
    print("\n计算的结果是: ")
    print(f"lim({expr_str}) = {result}")

if __name__ == "__main__":
    finnnn()
