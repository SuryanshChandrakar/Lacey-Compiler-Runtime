/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "compiler.yy"

#define YYSTYPE string
#define YYERROR_VERBOSE

extern int yylineno;
void yyerror(const char*);
extern int yylex (void);

#include<iostream>
#include<vector>
#include<map>
using namespace std;

string itoa(int i) {
	if(i == 0)
		return "0";
	string result;
	while(i > 0) {
		result = string(1, '0'+i%10) + result;
		i /= 10;
	}
	return result;
}

enum id_type {variable, procedure, constant};
class id_info {                                // class for symbol-table entries
	public:
		id_type type;
		int local_variables; // only for procedures
		int const_val; // only for constants
		int offset; // address of var in its frame
		int declaration_level;
		id_info() {}
};
id_info var_info(int offs, int lvl) {
	id_info info;
	info.type = variable;
	info.offset = offs;
	info.declaration_level = lvl;
	return info;
}
id_info const_info(int constval) {
	id_info info;
	info.type = constant;
	info.const_val = constval;
	return info;
}
id_info proc_info(int loc, int lvl) {
	id_info info;
	info.type = procedure;
	info.local_variables = loc;
	info.declaration_level = lvl;
	return info;
}

int jumplabel_counter = 1; // used to give unique names to all jump-labels (a1 a2...)
map<int, map<string, id_info> > symbol_table; // now every procedure gets its
                    // own symbol-table and can access the ones of higher frames
int level=0;
map<int,int> local_vars; // count of vars in current procedure


#line 134 "compiler.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INOUT = 258,                   /* INOUT  */
    VAR = 259,                     /* VAR  */
    CONST = 260,                   /* CONST  */
    PROC = 261,                    /* PROC  */
    OPEN = 262,                    /* OPEN  */
    CLOSE = 263,                   /* CLOSE  */
    SEMICOLON = 264,               /* SEMICOLON  */
    DOT = 265,                     /* DOT  */
    COMMA = 266,                   /* COMMA  */
    BEGN = 267,                    /* BEGN  */
    END = 268,                     /* END  */
    IF = 269,                      /* IF  */
    THEN = 270,                    /* THEN  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    DO = 273,                      /* DO  */
    ASSIGN = 274,                  /* ASSIGN  */
    NUM = 275,                     /* NUM  */
    ID = 276,                      /* ID  */
    ADD = 277,                     /* ADD  */
    SUB = 278,                     /* SUB  */
    MUL = 279,                     /* MUL  */
    DIV = 280,                     /* DIV  */
    EQ = 281,                      /* EQ  */
    NEQ = 282,                     /* NEQ  */
    GE = 283,                      /* GE  */
    GT = 284,                      /* GT  */
    LE = 285,                      /* LE  */
    LT = 286,                      /* LT  */
    OR = 287,                      /* OR  */
    AND = 288,                     /* AND  */
    NOT = 289,                     /* NOT  */
    MOD = 290                      /* MOD  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INOUT = 3,                      /* INOUT  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_CONST = 5,                      /* CONST  */
  YYSYMBOL_PROC = 6,                       /* PROC  */
  YYSYMBOL_OPEN = 7,                       /* OPEN  */
  YYSYMBOL_CLOSE = 8,                      /* CLOSE  */
  YYSYMBOL_SEMICOLON = 9,                  /* SEMICOLON  */
  YYSYMBOL_DOT = 10,                       /* DOT  */
  YYSYMBOL_COMMA = 11,                     /* COMMA  */
  YYSYMBOL_BEGN = 12,                      /* BEGN  */
  YYSYMBOL_END = 13,                       /* END  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_ASSIGN = 19,                    /* ASSIGN  */
  YYSYMBOL_NUM = 20,                       /* NUM  */
  YYSYMBOL_ID = 21,                        /* ID  */
  YYSYMBOL_ADD = 22,                       /* ADD  */
  YYSYMBOL_SUB = 23,                       /* SUB  */
  YYSYMBOL_MUL = 24,                       /* MUL  */
  YYSYMBOL_DIV = 25,                       /* DIV  */
  YYSYMBOL_EQ = 26,                        /* EQ  */
  YYSYMBOL_NEQ = 27,                       /* NEQ  */
  YYSYMBOL_GE = 28,                        /* GE  */
  YYSYMBOL_GT = 29,                        /* GT  */
  YYSYMBOL_LE = 30,                        /* LE  */
  YYSYMBOL_LT = 31,                        /* LT  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_MOD = 35,                       /* MOD  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_prog = 37,                      /* prog  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_39_2 = 39,                      /* $@2  */
  YYSYMBOL_const_decls = 40,               /* const_decls  */
  YYSYMBOL_const_ids = 41,                 /* const_ids  */
  YYSYMBOL_42_3 = 42,                      /* $@3  */
  YYSYMBOL_var_decls = 43,                 /* var_decls  */
  YYSYMBOL_var_ids = 44,                   /* var_ids  */
  YYSYMBOL_45_4 = 45,                      /* $@4  */
  YYSYMBOL_proc_decls = 46,                /* proc_decls  */
  YYSYMBOL_proc = 47,                      /* proc  */
  YYSYMBOL_48_5 = 48,                      /* $@5  */
  YYSYMBOL_49_6 = 49,                      /* $@6  */
  YYSYMBOL_statements = 50,                /* statements  */
  YYSYMBOL_statement = 51,                 /* statement  */
  YYSYMBOL_expression = 52,                /* expression  */
  YYSYMBOL_operator = 53                   /* operator  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  44
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  83

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    83,    83,    94,    95,    97,   105,   105,
     113,   114,   116,   124,   124,   132,   133,   135,   135,   135,
     150,   151,   153,   167,   181,   193,   195,   204,   221,   223,
     239,   241,   247,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INOUT", "VAR",
  "CONST", "PROC", "OPEN", "CLOSE", "SEMICOLON", "DOT", "COMMA", "BEGN",
  "END", "IF", "THEN", "ELSE", "WHILE", "DO", "ASSIGN", "NUM", "ID", "ADD",
  "SUB", "MUL", "DIV", "EQ", "NEQ", "GE", "GT", "LE", "LT", "OR", "AND",
  "NOT", "MOD", "$accept", "prog", "$@1", "$@2", "const_decls",
  "const_ids", "$@3", "var_decls", "var_ids", "$@4", "proc_decls", "proc",
  "$@5", "$@6", "statements", "statement", "expression", "operator", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-29)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       3,   -29,     8,   -10,   -29,     2,    10,   -29,   -29,   -10,
      28,   -29,    13,    31,    12,    27,   -10,    34,    21,   -29,
      33,    22,    -7,    34,    35,   -29,    38,    -7,    -3,    -3,
      -4,    39,   -29,   -29,   -29,    40,    41,    -3,   -29,   -29,
      -3,    56,    72,    43,    -3,   -29,    13,    28,   -29,    -7,
      37,    -2,    -7,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,    -3,    -7,   -29,    84,   -29,
      31,   -29,   -29,    32,    84,   -29,   -29,    -7,    34,   -29,
      -7,    45,   -29
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     2,     0,     0,     1,    12,     0,    13,     3,     0,
       5,    14,     0,    10,     0,     0,     0,    15,     0,     6,
       0,     0,     0,    15,     7,    11,     0,     0,     0,     0,
       0,     0,    16,     8,    17,     0,    20,     0,    28,    29,
       0,     0,     0,     0,     0,     4,     0,     5,    25,     0,
       0,    32,     0,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    44,    43,     0,     0,    23,    22,     9,
      10,    21,    30,    26,    31,    24,    18,     0,    15,    27,
       0,     0,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,   -29,   -29,     5,    26,   -29,   -14,    23,   -29,
     -21,   -29,   -29,   -29,    24,   -22,   -28,   -29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,    10,    13,    15,    46,    17,     6,     9,
      22,    23,    47,    78,    35,    36,    41,    65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    42,    32,    43,    37,    27,     1,    28,     4,    50,
      29,     5,    51,     7,    30,    44,    68,    38,    39,     8,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      73,    40,    11,    12,    14,    16,    19,    74,    18,    20,
      21,    24,    25,    26,    75,    72,    33,    34,    77,    45,
      49,    67,    70,    48,    82,    79,    76,    80,    81,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    52,    69,    71,     0,     0,     0,     0,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      66,     0,     0,     0,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64
};

static const yytype_int8 yycheck[] =
{
      22,    29,    23,     7,     7,    12,     3,    14,     0,    37,
      17,    21,    40,    11,    21,    19,    44,    20,    21,     9,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      52,    34,     9,     5,    21,     4,     9,    65,    26,    16,
       6,    20,     9,    21,    66,     8,    11,     9,    16,    10,
       9,     8,    47,    13,     9,    77,    70,    78,    80,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    15,    46,    49,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      18,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    37,    38,     0,    21,    44,    11,     9,    45,
      39,    44,     5,    40,    21,    41,     4,    43,    26,     9,
      44,     6,    46,    47,    20,     9,    21,    12,    14,    17,
      21,    51,    46,    11,     9,    50,    51,     7,    20,    21,
      34,    52,    52,     7,    19,    10,    42,    48,    13,     9,
      52,    52,    15,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    53,    18,     8,    52,    41,
      40,    50,     8,    51,    52,    51,    43,    16,    49,    51,
      46,    51,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    38,    39,    37,    40,    40,    41,    42,    41,
      43,    43,    44,    45,    44,    46,    46,    48,    49,    47,
      50,    50,    51,    51,    51,    51,    51,    51,    52,    52,
      52,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,    10,     0,     3,     3,     0,     6,
       0,     3,     1,     0,     4,     0,     2,     0,     0,    10,
       1,     3,     3,     3,     4,     3,     4,     6,     1,     1,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 83 "compiler.yy"
             {local_vars[0]=0;}
#line 1298 "compiler.cpp"
    break;

  case 3: /* $@2: %empty  */
#line 83 "compiler.yy"
                                                  {level=1;}
#line 1304 "compiler.cpp"
    break;

  case 4: /* prog: INOUT $@1 var_ids SEMICOLON $@2 const_decls var_decls proc_decls statement DOT  */
#line 83 "compiler.yy"
                                                                                                            {
           cout << "\tCALL aGamma 1 " << local_vars[1] << "\n"
                << "\tJMP 0\n"
                << yyvsp[-2]
                << "aGamma:\n"
                << yyvsp[-1]
                << "\tRET\n";
        }
#line 1317 "compiler.cpp"
    break;

  case 5: /* const_decls: %empty  */
#line 94 "compiler.yy"
              { yyval = ""; }
#line 1323 "compiler.cpp"
    break;

  case 6: /* const_decls: CONST const_ids SEMICOLON  */
#line 95 "compiler.yy"
                                        { yyval = ""; }
#line 1329 "compiler.cpp"
    break;

  case 7: /* const_ids: ID EQ NUM  */
#line 97 "compiler.yy"
                      {
                map<string, id_info>::iterator it = symbol_table[level].find(yyvsp[-2]);
                if(it == symbol_table[level].end())
                   symbol_table[level][yyvsp[-2]] = const_info(atoi(yyvsp[0].c_str()));
                else
                   cerr << "ERROR: (line " << yylineno << "): " << yyvsp[-2] << " is already declared";
                yyval = "";
             }
#line 1342 "compiler.cpp"
    break;

  case 8: /* $@3: %empty  */
#line 105 "compiler.yy"
                            {
                map<string, id_info>::iterator it = symbol_table[level].find(yyvsp[-3]);
                if(it == symbol_table[level].end())
                   symbol_table[level][yyvsp[-3]] = const_info(atoi(yyvsp[-1].c_str()));
                else
                   cerr << "ERROR: (line " << yylineno << "): " << yyvsp[-3] << " is already declared";
             }
#line 1354 "compiler.cpp"
    break;

  case 9: /* const_ids: ID EQ NUM COMMA $@3 const_ids  */
#line 111 "compiler.yy"
                         { yyval = ""; }
#line 1360 "compiler.cpp"
    break;

  case 10: /* var_decls: %empty  */
#line 113 "compiler.yy"
            {yyval="";}
#line 1366 "compiler.cpp"
    break;

  case 12: /* var_ids: ID  */
#line 116 "compiler.yy"
             {
              map<string, id_info>::iterator it = symbol_table[level].find(yyvsp[0]);
              if(it == symbol_table[level].end())
                 symbol_table[level][yyvsp[0]] = var_info(++local_vars[level], level);
              else
                 cerr << "ERROR: (line " << yylineno << "): " << yyvsp[0] << " is already declared";
              yyval = "";
           }
#line 1379 "compiler.cpp"
    break;

  case 13: /* $@4: %empty  */
#line 124 "compiler.yy"
                   {
              map<string, id_info>::iterator it = symbol_table[level].find(yyvsp[-1]);
              if(it == symbol_table[level].end())
                 symbol_table[level][yyvsp[-1]] = var_info(++local_vars[level], level);
              else
                 cerr << "ERROR: (line " << yylineno << "): " << yyvsp[-1] << " is already declared";
           }
#line 1391 "compiler.cpp"
    break;

  case 14: /* var_ids: ID COMMA $@4 var_ids  */
#line 130 "compiler.yy"
                     {yyval="";}
#line 1397 "compiler.cpp"
    break;

  case 15: /* proc_decls: %empty  */
#line 132 "compiler.yy"
             { yyval=""; }
#line 1403 "compiler.cpp"
    break;

  case 16: /* proc_decls: proc proc_decls  */
#line 133 "compiler.yy"
                             {yyval = yyvsp[-1]+yyvsp[0];}
#line 1409 "compiler.cpp"
    break;

  case 17: /* $@5: %empty  */
#line 135 "compiler.yy"
                         {local_vars[++level]=0; symbol_table[level].clear();}
#line 1415 "compiler.cpp"
    break;

  case 18: /* $@6: %empty  */
#line 135 "compiler.yy"
                                                                                                      {
           map<string, id_info>::iterator it = symbol_table[level].find(yyvsp[-4]);
           if(it == symbol_table[level].end())
              symbol_table[level][yyvsp[-4]] = proc_info(local_vars[level], level-1);
           else
              cerr << "ERROR: (line " << yylineno << "): " << yyvsp[-4] << " is already declared";
        }
#line 1427 "compiler.cpp"
    break;

  case 19: /* proc: PROC ID SEMICOLON $@5 const_decls var_decls $@6 proc_decls statement SEMICOLON  */
#line 141 "compiler.yy"
                                         {
           yyval = yyvsp[-2] + yyvsp[-8] + ":\n" + yyvsp[-1] + "\tRET\n";
           level--;
        }
#line 1436 "compiler.cpp"
    break;

  case 20: /* statements: statement  */
#line 150 "compiler.yy"
                       {yyval = yyvsp[0];}
#line 1442 "compiler.cpp"
    break;

  case 21: /* statements: statement SEMICOLON statements  */
#line 151 "compiler.yy"
                                            {yyval = yyvsp[-2] + yyvsp[0];}
#line 1448 "compiler.cpp"
    break;

  case 22: /* statement: ID ASSIGN expression  */
#line 153 "compiler.yy"
                                 {
                for(int i = level; i >= 0; --i) {
                   map<string, id_info>::iterator it = symbol_table[i].find(yyvsp[-2]);
                   if(it != symbol_table[i].end()) {
                      if(it->second.type == variable)
                         yyval = yyvsp[0] + "\tSTO " + itoa(level-it->second.declaration_level) + " " + itoa(it->second.offset) + "\n";
                      else
                         cerr << "ERROR (line " << yylineno << "): "  << yyvsp[-2] << " is not a variable\n";
                   goto assign_found;}
                }
                cerr << "ERROR (line " << yylineno << "): "  << yyvsp[-2] << " is not declared\n";
                assign_found:;
             }
#line 1466 "compiler.cpp"
    break;

  case 23: /* statement: ID OPEN CLOSE  */
#line 167 "compiler.yy"
                          {
                for(int i = level; i >= 0; --i) {
                   map<string, id_info>::iterator it = symbol_table[i].find(yyvsp[-2]);
                   if(it != symbol_table[i].end()) {
                      if(it->second.type == procedure)
                         yyval = "\tCALL " + yyvsp[-2] + " " + itoa(level-it->second.declaration_level) + " " + itoa(it->second.local_variables) + "\n";
                      else
                         cerr << "ERROR (line " << yylineno << "): "  << yyvsp[-2] << " is not a procedure\n";
                   goto proc_found;}
                }
                cerr << "ERROR (line " << yylineno << "): "  << yyvsp[-2] << " is not declared\n";
                proc_found:;
             }
#line 1484 "compiler.cpp"
    break;

  case 24: /* statement: WHILE expression DO statement  */
#line 181 "compiler.yy"
                                          {
                string jump1 = "a"+itoa(jumplabel_counter);
                string jump2 = "a"+itoa(jumplabel_counter+1);
                jumplabel_counter += 2;
                yyval = jump1 + ":\n"
                   + yyvsp[-2]                      // code to test the condition
                   + "\tJFALSE " + jump2 + "\n"  // if false, jump behind looped code
                   + yyvsp[0]                      // looped code
                   + "\tJMP " + jump1 + "\n" // jump back to testing the condition
                   + jump2 + ":\n";
             }
#line 1500 "compiler.cpp"
    break;

  case 25: /* statement: BEGN statements END  */
#line 193 "compiler.yy"
                                { yyval = yyvsp[-1]; }
#line 1506 "compiler.cpp"
    break;

  case 26: /* statement: IF expression THEN statement  */
#line 195 "compiler.yy"
                                         {
                string jump1 = "a"+itoa(jumplabel_counter);
                jumplabel_counter++;
                yyval = yyvsp[-2]                     // code to test the condition
                   + "\tJFALSE " + jump1 + "\n" // if false, jump behind then-codeblock
                   + yyvsp[0]                     // then-codeblock
                   + jump1 + ":\n";
             }
#line 1519 "compiler.cpp"
    break;

  case 27: /* statement: IF expression THEN statement ELSE statement  */
#line 204 "compiler.yy"
                                                        {
                string jump1 = "a"+itoa(jumplabel_counter);
                string jump2 = "a"+itoa(jumplabel_counter+1);
                jumplabel_counter += 2;

                yyval = yyvsp[-4]                      // code to test the condition
                   + "\tJFALSE " + jump1 + "\n"  // if false, jump to else-codeblock
                   + yyvsp[-2]                      // then-codeblock
                   + "\tJMP " + jump2 + "\n" // jump behind else-codeblock
                   + jump1 + ":\n"
                   + yyvsp[0]                      // else-codeblock
                   + jump2 + ":\n";
             }
#line 1537 "compiler.cpp"
    break;

  case 28: /* expression: NUM  */
#line 221 "compiler.yy"
                 { yyval = "\tLIT "+yyvsp[0]+"\n"; }
#line 1543 "compiler.cpp"
    break;

  case 29: /* expression: ID  */
#line 223 "compiler.yy"
                {
                 for(int i = level; i >= 0; --i) {
                    map<string, id_info>::iterator it = symbol_table[i].find(yyvsp[0]);
                    if(it != symbol_table[i].end()) {
                       if(it->second.type == variable)
                          yyval = "\tLOAD " + itoa(level-it->second.declaration_level) + " " + itoa(it->second.offset) + "\n";
                       else if(it->second.type == constant)
                          yyval = "\tLIT " + itoa(it->second.const_val) + "\n";
                       else
                          cerr << "ERROR (line " << yylineno << "): "  << yyvsp[0] << " is not a variable\n";
                    goto id_found;}
                 }
                 cerr << "ERROR (line " << yylineno << "): "  << yyvsp[0] << " is not declared\n";
                 id_found:;
              }
#line 1563 "compiler.cpp"
    break;

  case 30: /* expression: OPEN expression CLOSE  */
#line 239 "compiler.yy"
                                   { yyval = yyvsp[-1]; }
#line 1569 "compiler.cpp"
    break;

  case 31: /* expression: expression operator expression  */
#line 241 "compiler.yy"
                                            {
                 yyval = yyvsp[-2]  // evaluate first expression (and push result on stack)
                    + yyvsp[0]  // evaluate second expression (and push result on stack)
                    + yyvsp[-1]; // calculare result, depending on the operator
              }
#line 1579 "compiler.cpp"
    break;

  case 32: /* expression: NOT expression  */
#line 247 "compiler.yy"
                            { yyval = yyvsp[0] + "\tNOT\n"; }
#line 1585 "compiler.cpp"
    break;

  case 33: /* operator: ADD  */
#line 250 "compiler.yy"
                {yyval = "\tADD\n";}
#line 1591 "compiler.cpp"
    break;

  case 34: /* operator: SUB  */
#line 251 "compiler.yy"
                {yyval = "\tSUB\n";}
#line 1597 "compiler.cpp"
    break;

  case 35: /* operator: MUL  */
#line 252 "compiler.yy"
                {yyval = "\tMULT\n";}
#line 1603 "compiler.cpp"
    break;

  case 36: /* operator: DIV  */
#line 253 "compiler.yy"
                {yyval = "\tDIV\n";}
#line 1609 "compiler.cpp"
    break;

  case 37: /* operator: EQ  */
#line 254 "compiler.yy"
                {yyval = "\tEQ\n";}
#line 1615 "compiler.cpp"
    break;

  case 38: /* operator: NEQ  */
#line 255 "compiler.yy"
                {yyval = "\tNEQ\n";}
#line 1621 "compiler.cpp"
    break;

  case 39: /* operator: GE  */
#line 256 "compiler.yy"
                {yyval = "\tGE\n";}
#line 1627 "compiler.cpp"
    break;

  case 40: /* operator: GT  */
#line 257 "compiler.yy"
                {yyval = "\tGT\n";}
#line 1633 "compiler.cpp"
    break;

  case 41: /* operator: LE  */
#line 258 "compiler.yy"
                {yyval = "\tLE\n";}
#line 1639 "compiler.cpp"
    break;

  case 42: /* operator: LT  */
#line 259 "compiler.yy"
                {yyval = "\tLT\n";}
#line 1645 "compiler.cpp"
    break;

  case 43: /* operator: AND  */
#line 260 "compiler.yy"
                {yyval = "\tAND\n";}
#line 1651 "compiler.cpp"
    break;

  case 44: /* operator: OR  */
#line 261 "compiler.yy"
                {yyval = "\tOR\n";}
#line 1657 "compiler.cpp"
    break;


#line 1661 "compiler.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 266 "compiler.yy"


#include "lexer.cpp" // lexer einbinden

void yyerror(const char* s)
{
	cerr << "SYNTACTIC ERROR (Line " << yylineno << "): " << s << endl;
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cerr << argv[0] << " needs a bps sourcecode as parameter\n";
		return 1;
	}
	yyin = fopen(argv[1], "r");
	yyparse();
	if(yynerrs != 0)
	{
		cerr << " " << yynerrs << " syntactic errors occured\n";
		return 1;
	}
	return 0;
}
