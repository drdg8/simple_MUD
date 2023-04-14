# -include foo.make *.mk $(bar)

# 找路径
# VPATH = src:../headers

# vpath %.h ../headers
# vpath %.c foo:bar
# vpath %   blish

# Makefile中的第一个目标会被作为其默认目标(就算是伪目标)
# all : prog1 prog2 prog3
# .PHONY : all

# 多目标
# bigoutput littleoutput : text.g
#     generate text.g -$(subst output,,$@) > $@
# 其中， -$(subst output,,$@) 中的 $ 表示执行一个Makefile的函数，函数名为subst，后面的为参数。 -表示强制执行不显示错误
# 这里的这个函数是替换字符串的意思， $@ 表示目标的集合，就像一个数组， $@ 依次取出目标，并执于命令。

# 静态模式eg:
# files = foo.elc bar.o lose.o
# 
# $(filter %.o,$(files)): %.o: %.c
#     $(CC) -c $(CFLAGS) $< -o $@
# $(filter %.elc,$(files)): %.elc: %.el
#     emacs -f batch-byte-compile $<

# $(filter %.o,$(files))表示调用Makefile的filter函数，过滤“$files”集，只要其中模式为“%.o”的内容。
# 上面的例子中，指明了我们的目标从$object中获取， %.o 表明要所有以 .o 结尾的目标，也就是 foo.o bar.o ，也就是变量 $object 集合的模式
# 而依赖模式 %.c 则取模式 %.o 的 % ，也就是 foo bar ，并为其加下 .c 的后缀，于是，我们的依赖目标就是 foo.c bar.c 。
# 而命令中的 $< 和 $@ 则是自动化变量， $< 表示第一个依赖文件， $@ 表示目标集（也就是“foo.o bar.o”）

# 自动生成依赖性
# 感觉用不到所以请参考
# https://seisman.github.io/how-to-write-makefile/rules.html

# 定义命令包

# := 前面的变量不能使用后面的变量 是为了防止递归定义
Obj := Skill.o Item.o Armor.o Food.o Weapon.o Inventory.o Character.o \
	NPC.o Trader.o Scene.o Game.o main.o

main: $(Obj)
	g++ -o main $(Obj)

# Skill.o
Item.o: Skill.o
Armor.o: Item.o
Food.o: Item.o
Weapon.o: Item.o
Inventory.o: Armor.o Food.o Weapon.o
Character.o: Inventory.o
NPC.o: Character.o
Trader.o: NPC.o
Scene.o: Trader.o
Game.o: Scene.o
main.o: main.cpp Game.o
	g++ -c main.cpp
	@echo 正在编译主程序

# Makefile中的变量其实就是C/C++中的宏。
# objects := $(patsubst %.c,%.o,$(wildcard *.c))
# foo : $(objects)
#     cc -o foo $(objects)

# subsystem:
#     cd subdir && $(MAKE)

# 如果你要传递变量到下级Makefile中，那么你可以使用这样的声明:
# export <variable ...>; (没有参数意味着全部传递)
# 有两个变量，一个是 SHELL ，一个是 MAKEFLAGS ，这两个变量不管你是否export，其总是要传递到下层 Makefile中
# MAKEFLAGS 变量，其中包含了make的参数信息,是一个系统级的环境变量。

.PHONY: clean
clean:
	-rm main $(Obj)

# make 参数
# -k 或是 --keep-going ，这个参数的意思是，如果某规则中的命令出错了，那么就终止该规则的执行，但继续执行其它规则。
# -i 或是 --ignore-errors 参数，那么，Makefile中所有命令都会忽略错误。
# -s 或 --silent 或 --quiet 则是全面禁止命令的显示。
# -n 或 --just-print ，那么其只是显示命令，但不会执行命令，
# -w 或是 --print-directory 会在make的过程中输出一些信息，让你看到目前的工作目录。

# 使用变量之后没笔记 自己看

# https://blog.csdn.net/fpgatom/article/details/84171808

# lex.yy.c: *.l
# 	@flex $<
# 
# a.exe: lex.yy.c
# 	gcc lex.yy.c
# 
# .PHONY: all clean
# all: a.exe
# 	./a.exe
# 
# clean:
# 	-rm a.exe
