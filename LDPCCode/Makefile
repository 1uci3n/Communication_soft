#
#Makefile
#
CC	=		g++			# コンパイラ

SOURCES	=	SumproductTools.cpp		\
			Sumproduct.cpp			\
			TestCode.cpp

OBJECTS	=	$(SOURCES:.c=.o)	# [.obj] file
TARGET	=	Test				# 実行フェイル名

# 生成規則

# 実行ファイル生成コマンド
# .obj のリンクを行う
$(TARGET):	$(OBJECTS)
			$(CC) -o $@ $(OBJECTS)
# サフィックスルール
# .c から .oの作成
.c.o:
			$(CC) -c -Wall $< -o $@

# オブジェクトファイルの削除
clean:
			rm *.o *~ $(TARGET) -rf
