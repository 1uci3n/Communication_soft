#
#makefile
#
CC	=		g++			# コンパイラ

SOURCES	=	../CommonFiles/RandomTools.cpp			\
			../CommonFiles/OutputTools.cpp			\
			../CommonFiles/VectorTools.cpp			\
			../CommonFiles/NumberSystemTools.cpp	\
			../CommonFiles/GaussianChannel2nd.cpp	\
			SumproductTools.cpp		\
			Sumproduct.cpp			\
			HammingCode.cpp			\
			OutputEffective.cpp

OBJECTS	=	$(SOURCES:.c=.o)	# [.obj] file
TARGET	=	Test				# 実行ファイル名

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
