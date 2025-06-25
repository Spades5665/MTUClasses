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


/* Substitute the variable and function names.  */
#define yyparse         Cminus_parse
#define yylex           Cminus_lex
#define yyerror         Cminus_error
#define yydebug         Cminus_debug
#define yynerrs         Cminus_nerrs
#define yylval          Cminus_lval
#define yychar          Cminus_char

/* First part of user prologue.  */
#line 7 "CminusParser.y"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <util/general.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/dlink.h>
#include <util/string_utils.h>
#include <codegen/symfields.h>
#include <codegen/types.h>
#include <codegen/codegen.h>
#include <codegen/reg.h>

#define SYMTABLE_SIZE 100

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void, Cminus_error, (char*));

EXTERN(int, Cminus_lex, (void));

char *fileName;
int labelNum = 0;
int globalOffset = 0;
static int functionOffset;
static char* functionName;

static DList instList;
static DList dataList;
SymTable symtab;

extern union YYSTYPE yylval;
extern int Cminus_lineno;


#line 116 "CminusParser.c"

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

#include "CminusParser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_AND = 3,                        /* AND  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_EXIT = 5,                       /* EXIT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_FOR = 7,                        /* FOR  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_INTEGER = 9,                    /* INTEGER  */
  YYSYMBOL_NOT = 10,                       /* NOT  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_READ = 12,                      /* READ  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_WRITE = 14,                     /* WRITE  */
  YYSYMBOL_LBRACE = 15,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 16,                    /* RBRACE  */
  YYSYMBOL_LE = 17,                        /* LE  */
  YYSYMBOL_LT = 18,                        /* LT  */
  YYSYMBOL_GE = 19,                        /* GE  */
  YYSYMBOL_GT = 20,                        /* GT  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NE = 22,                        /* NE  */
  YYSYMBOL_ASSIGN = 23,                    /* ASSIGN  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 25,                 /* SEMICOLON  */
  YYSYMBOL_LBRACKET = 26,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 27,                  /* RBRACKET  */
  YYSYMBOL_LPAREN = 28,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 29,                    /* RPAREN  */
  YYSYMBOL_PLUS = 30,                      /* PLUS  */
  YYSYMBOL_TIMES = 31,                     /* TIMES  */
  YYSYMBOL_IDENTIFIER = 32,                /* IDENTIFIER  */
  YYSYMBOL_DIVIDE = 33,                    /* DIVIDE  */
  YYSYMBOL_RETURN = 34,                    /* RETURN  */
  YYSYMBOL_STRING = 35,                    /* STRING  */
  YYSYMBOL_INTCON = 36,                    /* INTCON  */
  YYSYMBOL_FLOATCON = 37,                  /* FLOATCON  */
  YYSYMBOL_MINUS = 38,                     /* MINUS  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Program = 40,                   /* Program  */
  YYSYMBOL_Procedures = 41,                /* Procedures  */
  YYSYMBOL_ProcedureDecl = 42,             /* ProcedureDecl  */
  YYSYMBOL_ProcedureHead = 43,             /* ProcedureHead  */
  YYSYMBOL_FunctionDecl = 44,              /* FunctionDecl  */
  YYSYMBOL_ProcedureBody = 45,             /* ProcedureBody  */
  YYSYMBOL_DeclList = 46,                  /* DeclList  */
  YYSYMBOL_IdentifierList = 47,            /* IdentifierList  */
  YYSYMBOL_VarDecl = 48,                   /* VarDecl  */
  YYSYMBOL_Type = 49,                      /* Type  */
  YYSYMBOL_Statement = 50,                 /* Statement  */
  YYSYMBOL_Assignment = 51,                /* Assignment  */
  YYSYMBOL_IfStatement = 52,               /* IfStatement  */
  YYSYMBOL_TestAndThen = 53,               /* TestAndThen  */
  YYSYMBOL_Test = 54,                      /* Test  */
  YYSYMBOL_WhileStatement = 55,            /* WhileStatement  */
  YYSYMBOL_WhileExpr = 56,                 /* WhileExpr  */
  YYSYMBOL_WhileToken = 57,                /* WhileToken  */
  YYSYMBOL_IOStatement = 58,               /* IOStatement  */
  YYSYMBOL_ReturnStatement = 59,           /* ReturnStatement  */
  YYSYMBOL_ExitStatement = 60,             /* ExitStatement  */
  YYSYMBOL_CompoundStatement = 61,         /* CompoundStatement  */
  YYSYMBOL_StatementList = 62,             /* StatementList  */
  YYSYMBOL_Expr = 63,                      /* Expr  */
  YYSYMBOL_SimpleExpr = 64,                /* SimpleExpr  */
  YYSYMBOL_AddExpr = 65,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 66,                   /* MulExpr  */
  YYSYMBOL_Factor = 67,                    /* Factor  */
  YYSYMBOL_Variable = 68,                  /* Variable  */
  YYSYMBOL_StringConstant = 69,            /* StringConstant  */
  YYSYMBOL_Constant = 70                   /* Constant  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   109,   109,   114,   122,   123,   126,   132,   138,   146,
     153,   156,   169,   184,   189,   196,   202,   211,   212,   215,
     216,   217,   218,   219,   220,   221,   224,   230,   234,   240,
     246,   253,   259,   266,   273,   277,   281,   287,   290,   296,
     299,   300,   303,   307,   311,   315,   321,   325,   329,   333,
     337,   341,   345,   351,   355,   359,   365,   369,   373,   379,
     383,   387,   392,   398,   404,   412,   420
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
  "\"end of file\"", "error", "\"invalid token\"", "AND", "ELSE", "EXIT",
  "FLOAT", "FOR", "IF", "INTEGER", "NOT", "OR", "READ", "WHILE", "WRITE",
  "LBRACE", "RBRACE", "LE", "LT", "GE", "GT", "EQ", "NE", "ASSIGN",
  "COMMA", "SEMICOLON", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "PLUS",
  "TIMES", "IDENTIFIER", "DIVIDE", "RETURN", "STRING", "INTCON",
  "FLOATCON", "MINUS", "$accept", "Program", "Procedures", "ProcedureDecl",
  "ProcedureHead", "FunctionDecl", "ProcedureBody", "DeclList",
  "IdentifierList", "VarDecl", "Type", "Statement", "Assignment",
  "IfStatement", "TestAndThen", "Test", "WhileStatement", "WhileExpr",
  "WhileToken", "IOStatement", "ReturnStatement", "ExitStatement",
  "CompoundStatement", "StatementList", "Expr", "SimpleExpr", "AddExpr",
  "MulExpr", "Factor", "Variable", "StringConstant", "Constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-49)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,   -49,   -49,     3,   -49,    -2,    37,    -2,    -2,   -12,
     -49,   -49,     6,    18,    46,    64,   -49,    80,    37,    52,
      34,   -49,   -49,   -49,   -49,   -49,    95,   -49,   -49,   -49,
     -49,     1,    40,    -2,    72,   -49,   -12,   -18,    76,   -49,
      98,   -49,    34,   125,   115,    99,    48,    14,    34,    66,
      34,    71,   -49,    78,    94,    35,    44,   -49,   -49,   -49,
      34,    37,   -49,   -49,    34,    72,   106,    82,    97,   105,
      72,   -49,    50,   115,   -49,   107,   -49,    56,   108,   -49,
      20,    94,    57,   109,    66,    66,   -49,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    61,   -49,    85,
     -49,   112,   120,   -49,   -49,   -49,   116,   117,   118,   -49,
     -49,   -49,    94,    94,    35,    35,    35,    35,    35,    35,
      44,    44,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    18,    17,     0,     2,     5,     0,     8,     5,     0,
       1,     4,     0,     0,     0,     0,    33,     0,     0,    63,
       0,     6,    40,    19,    20,    21,     0,    22,    23,    24,
      25,     0,     0,     7,     0,     3,     0,    15,     0,    13,
       0,    38,     0,    28,     0,     0,     0,     0,     0,     0,
       0,    63,    66,     0,    42,    46,    53,    56,    59,    60,
       0,     0,    10,    41,     0,     0,    15,     0,     0,     0,
       0,    11,     0,     0,    29,     0,    65,     0,     0,    39,
       0,    45,     0,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
      12,     0,     0,    14,    30,    27,     0,     0,     0,    64,
      62,    61,    44,    43,    49,    50,    51,    52,    47,    48,
      54,    55,    57,    58,    32,    26,    16,     9,    34,    35,
      36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,    16,   -49,   -49,   -49,   -49,   133,   -31,    74,
      49,   -29,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -33,   127,    45,   -48,    30,    31,    32,    -6,
     -49,   -49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,    21,     8,    38,    39,
       9,    22,    23,    24,    43,    44,    25,    61,    26,    27,
      28,    29,    30,    31,    53,    54,    55,    56,    57,    58,
      78,    59
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      32,    81,    63,    10,     1,    67,    13,     2,    68,    14,
      69,    74,    32,    15,    16,    17,    18,    62,    63,    13,
      37,    11,    14,    84,    35,    32,    15,    16,    17,    18,
      79,    85,    98,    19,    67,    20,   112,   113,    40,    75,
     105,    32,    13,    41,    49,    14,    19,   109,    20,    15,
      16,    17,    18,    84,    12,    32,    34,    36,    49,    84,
      84,    85,    50,    64,    84,    93,    51,    85,    85,    19,
      52,    20,    85,    94,    42,    95,    50,    96,    48,   104,
      51,    84,    65,    76,    52,   107,   110,    72,    84,    85,
     124,    77,    45,    80,    50,    82,    85,    48,    51,    83,
      70,    71,    52,    86,    66,    97,    70,   100,    46,    99,
     125,    87,    88,    89,    90,    91,    92,   114,   115,   116,
     117,   118,   119,    60,   120,   121,    69,   122,   123,    73,
      18,    19,    68,   101,   102,   127,   106,   108,   111,   126,
      33,   128,   129,   130,   103,    47
};

static const yytype_int8 yycheck[] =
{
       6,    49,    31,     0,     6,    36,     5,     9,    26,     8,
      28,    44,    18,    12,    13,    14,    15,    16,    47,     5,
      32,     5,     8,     3,     8,    31,    12,    13,    14,    15,
      16,    11,    61,    32,    65,    34,    84,    85,    32,    45,
      73,    47,     5,    25,    10,     8,    32,    27,    34,    12,
      13,    14,    15,     3,     5,    61,     7,     8,    10,     3,
       3,    11,    28,    23,     3,    30,    32,    11,    11,    32,
      36,    34,    11,    38,    28,    31,    28,    33,    26,    29,
      32,     3,    33,    35,    36,    29,    29,    42,     3,    11,
      29,    46,    28,    48,    28,    50,    11,    26,    32,    28,
      24,    25,    36,    25,    32,    60,    24,    25,    28,    64,
      25,    17,    18,    19,    20,    21,    22,    87,    88,    89,
      90,    91,    92,    28,    93,    94,    28,    95,    96,     4,
      15,    32,    26,    36,    29,    15,    29,    29,    29,    27,
       7,    25,    25,    25,    70,    18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     9,    40,    41,    42,    43,    44,    46,    49,
       0,    41,    49,     5,     8,    12,    13,    14,    15,    32,
      34,    45,    50,    51,    52,    55,    57,    58,    59,    60,
      61,    62,    68,    46,    49,    41,    49,    32,    47,    48,
      32,    25,    28,    53,    54,    28,    28,    62,    26,    10,
      28,    32,    36,    63,    64,    65,    66,    67,    68,    70,
      28,    56,    16,    50,    23,    49,    32,    47,    26,    28,
      24,    25,    63,     4,    61,    68,    35,    63,    69,    16,
      63,    64,    63,    28,     3,    11,    25,    17,    18,    19,
      20,    21,    22,    30,    38,    31,    33,    63,    50,    63,
      25,    36,    29,    48,    29,    61,    29,    29,    29,    27,
      29,    29,    64,    64,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    67,    29,    25,    27,    15,    25,    25,
      25
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    41,    41,    42,    43,    43,    44,
      45,    46,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    50,    50,    50,    50,    50,    51,    52,    52,    53,
      54,    55,    56,    57,    58,    58,    58,    59,    60,    61,
      62,    62,    63,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    65,    65,    65,    66,    66,    66,    67,
      67,    67,    67,    68,    68,    69,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     2,     2,     1,     5,
       2,     3,     4,     1,     3,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     2,     2,
       3,     3,     3,     1,     5,     5,     5,     3,     2,     3,
       1,     2,     1,     3,     3,     2,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       1,     3,     3,     1,     4,     1,     1
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
  case 2: /* Program: Procedures  */
#line 110 "CminusParser.y"
                                {
					emitDataPrologue(dataList);
					emitInstructions(instList);
				}
#line 1267 "CminusParser.c"
    break;

  case 3: /* Program: DeclList Procedures  */
#line 115 "CminusParser.y"
                                {
					globalOffset = (yyvsp[-1].offset);
					emitDataPrologue(dataList);
					emitInstructions(instList);
				}
#line 1277 "CminusParser.c"
    break;

  case 6: /* ProcedureDecl: ProcedureHead ProcedureBody  */
#line 127 "CminusParser.y"
                {
					emitExit(instList);
               	}
#line 1285 "CminusParser.c"
    break;

  case 7: /* ProcedureHead: FunctionDecl DeclList  */
#line 133 "CminusParser.y"
                                {
					emitProcedurePrologue(instList, symtab, (yyvsp[-1].symIndex), (yyvsp[0].offset));
					functionOffset = (yyvsp[0].offset);
					(yyval.symIndex) = (yyvsp[-1].symIndex);
				}
#line 1295 "CminusParser.c"
    break;

  case 8: /* ProcedureHead: FunctionDecl  */
#line 139 "CminusParser.y"
                                {
					emitProcedurePrologue(instList, symtab, (yyvsp[0].symIndex), 0);
					functionOffset = 0;
					(yyval.symIndex) = (yyvsp[0].symIndex);
				}
#line 1305 "CminusParser.c"
    break;

  case 9: /* FunctionDecl: Type IDENTIFIER LPAREN RPAREN LBRACE  */
#line 147 "CminusParser.y"
                                {
					(yyval.symIndex) = SymIndex(symtab, (yyvsp[-3].name));
					free((yyvsp[-3].name));
				}
#line 1314 "CminusParser.c"
    break;

  case 11: /* DeclList: Type IdentifierList SEMICOLON  */
#line 157 "CminusParser.y"
                                {
					AddIdStructPtr data = (AddIdStructPtr) malloc(sizeof(AddIdStruct));
					data->offset = 0;
					data->offsetDirection = 1;
					data->symtab = symtab;
					dlinkApply1((yyvsp[-1].idList), (DLinkApply1Func) addIdToSymtab, (Generic) data);
					(yyval.offset) = data->offset;
					dlinkFreeNodes((yyvsp[-1].idList));
					dlinkListFree((yyvsp[-1].idList));
					
					free(data);
				}
#line 1331 "CminusParser.c"
    break;

  case 12: /* DeclList: DeclList Type IdentifierList SEMICOLON  */
#line 170 "CminusParser.y"
                                {
					AddIdStructPtr data = (AddIdStructPtr) malloc(sizeof(AddIdStruct));
					data->offset = (yyvsp[-3].offset);
					data->offsetDirection = 1;
					data->symtab = symtab;
					dlinkApply1((yyvsp[-1].idList), (DLinkApply1Func) addIdToSymtab, (Generic) data);
					(yyval.offset) = data->offset;
					dlinkFreeNodes((yyvsp[-1].idList));
					dlinkListFree((yyvsp[-1].idList));

					free(data);
				}
#line 1348 "CminusParser.c"
    break;

  case 13: /* IdentifierList: VarDecl  */
#line 185 "CminusParser.y"
                                {
					(yyval.idList) = dlinkListAlloc(NULL);
					dlinkAppend((yyval.idList), dlinkNodeAlloc((Generic) (yyvsp[0].symIndex)));
				}
#line 1357 "CminusParser.c"
    break;

  case 14: /* IdentifierList: IdentifierList COMMA VarDecl  */
#line 190 "CminusParser.y"
                                {
					(yyval.idList) = (yyvsp[-2].idList);
					dlinkAppend((yyval.idList), dlinkNodeAlloc((Generic) (yyvsp[0].symIndex)));
				}
#line 1366 "CminusParser.c"
    break;

  case 15: /* VarDecl: IDENTIFIER  */
#line 197 "CminusParser.y"
                                { 
					(yyval.symIndex) = SymIndex(symtab, (yyvsp[0].name));
					free((yyvsp[0].name));
					SymPutFieldByIndex(symtab, (yyval.symIndex), SYMTAB_OFFSET_FIELD, (Generic) 0);
				}
#line 1376 "CminusParser.c"
    break;

  case 16: /* VarDecl: IDENTIFIER LBRACKET INTCON RBRACKET  */
#line 203 "CminusParser.y"
                                {
					(yyval.symIndex) = SymIndex(symtab, (yyvsp[-3].name));
					free((yyvsp[-3].name));
					SymPutFieldByIndex(symtab, (yyval.symIndex), SYMTAB_OFFSET_FIELD, (Generic) (atoi((yyvsp[-1].name)) - 1));
					free((yyvsp[-1].name));
				}
#line 1387 "CminusParser.c"
    break;

  case 26: /* Assignment: Variable ASSIGN Expr SEMICOLON  */
#line 225 "CminusParser.y"
                                {
					emitAssignment(instList, symtab, (yyvsp[-3].symIndex), (yyvsp[-1].symIndex));
				}
#line 1395 "CminusParser.c"
    break;

  case 27: /* IfStatement: IF TestAndThen ELSE CompoundStatement  */
#line 231 "CminusParser.y"
                                {
					emitIfEnd(instList, symtab, (yyvsp[-2].offset));
				}
#line 1403 "CminusParser.c"
    break;

  case 28: /* IfStatement: IF TestAndThen  */
#line 235 "CminusParser.y"
                                {
					emitIfEnd(instList, symtab, (yyvsp[0].offset));
				}
#line 1411 "CminusParser.c"
    break;

  case 29: /* TestAndThen: Test CompoundStatement  */
#line 241 "CminusParser.y"
                                {
					(yyval.offset) = emitIfElse(instList, symtab, (yyvsp[-1].offset));
				}
#line 1419 "CminusParser.c"
    break;

  case 30: /* Test: LPAREN Expr RPAREN  */
#line 247 "CminusParser.y"
                                {
					(yyval.offset) = emitIfEvaluate(instList, symtab, (yyvsp[-1].symIndex), labelNum);
					labelNum += 2;
				}
#line 1428 "CminusParser.c"
    break;

  case 31: /* WhileStatement: WhileToken WhileExpr Statement  */
#line 254 "CminusParser.y"
                                {
					emitWhileEnd(instList, symtab, (yyvsp[-2].offset), (yyvsp[-1].offset));
				}
#line 1436 "CminusParser.c"
    break;

  case 32: /* WhileExpr: LPAREN Expr RPAREN  */
#line 260 "CminusParser.y"
                                {
					(yyval.offset) = emitWhileEval(instList, symtab, (yyvsp[-1].symIndex), labelNum);
					labelNum++;
				}
#line 1445 "CminusParser.c"
    break;

  case 33: /* WhileToken: WHILE  */
#line 267 "CminusParser.y"
                                {
					(yyval.offset) = emitWhileStart(instList, symtab, labelNum);
					labelNum++;
				}
#line 1454 "CminusParser.c"
    break;

  case 34: /* IOStatement: READ LPAREN Variable RPAREN SEMICOLON  */
#line 274 "CminusParser.y"
                                {
					emitReadVariable(instList, symtab, (yyvsp[-2].symIndex));
				}
#line 1462 "CminusParser.c"
    break;

  case 35: /* IOStatement: WRITE LPAREN Expr RPAREN SEMICOLON  */
#line 278 "CminusParser.y"
                                {
					emitWriteExpression(instList, symtab, (yyvsp[-2].symIndex), SYSCALL_PRINT_INTEGER);
				}
#line 1470 "CminusParser.c"
    break;

  case 36: /* IOStatement: WRITE LPAREN StringConstant RPAREN SEMICOLON  */
#line 282 "CminusParser.y"
                                {
					emitWriteExpression(instList, symtab, (yyvsp[-2].symIndex), SYSCALL_PRINT_STRING);
				}
#line 1478 "CminusParser.c"
    break;

  case 38: /* ExitStatement: EXIT SEMICOLON  */
#line 291 "CminusParser.y"
                                {
					emitExit(instList);
				}
#line 1486 "CminusParser.c"
    break;

  case 42: /* Expr: SimpleExpr  */
#line 304 "CminusParser.y"
                                {
					(yyval.symIndex) = (yyvsp[0].symIndex); 
				}
#line 1494 "CminusParser.c"
    break;

  case 43: /* Expr: Expr OR SimpleExpr  */
#line 308 "CminusParser.y"
                                {
					(yyval.symIndex) = emitOrExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1502 "CminusParser.c"
    break;

  case 44: /* Expr: Expr AND SimpleExpr  */
#line 312 "CminusParser.y"
                                {
					(yyval.symIndex) = emitAndExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1510 "CminusParser.c"
    break;

  case 45: /* Expr: NOT SimpleExpr  */
#line 316 "CminusParser.y"
                                {
					(yyval.symIndex) = emitNotExpression(instList, symtab, (yyvsp[0].symIndex));
				}
#line 1518 "CminusParser.c"
    break;

  case 46: /* SimpleExpr: AddExpr  */
#line 322 "CminusParser.y"
                                {
					(yyval.symIndex) = (yyvsp[0].symIndex); 
				}
#line 1526 "CminusParser.c"
    break;

  case 47: /* SimpleExpr: SimpleExpr EQ AddExpr  */
#line 326 "CminusParser.y"
                                {
					(yyval.symIndex) = emitEqualExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1534 "CminusParser.c"
    break;

  case 48: /* SimpleExpr: SimpleExpr NE AddExpr  */
#line 330 "CminusParser.y"
                                {
					(yyval.symIndex) = emitNotEqualExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1542 "CminusParser.c"
    break;

  case 49: /* SimpleExpr: SimpleExpr LE AddExpr  */
#line 334 "CminusParser.y"
                                {
					(yyval.symIndex) = emitLessEqualExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1550 "CminusParser.c"
    break;

  case 50: /* SimpleExpr: SimpleExpr LT AddExpr  */
#line 338 "CminusParser.y"
                                {
					(yyval.symIndex) = emitLessThanExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1558 "CminusParser.c"
    break;

  case 51: /* SimpleExpr: SimpleExpr GE AddExpr  */
#line 342 "CminusParser.y"
                                {
					(yyval.symIndex) = emitGreaterEqualExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1566 "CminusParser.c"
    break;

  case 52: /* SimpleExpr: SimpleExpr GT AddExpr  */
#line 346 "CminusParser.y"
                                {
					(yyval.symIndex) = emitGreaterThanExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1574 "CminusParser.c"
    break;

  case 53: /* AddExpr: MulExpr  */
#line 352 "CminusParser.y"
                                {
					(yyval.symIndex) = (yyvsp[0].symIndex); 
				}
#line 1582 "CminusParser.c"
    break;

  case 54: /* AddExpr: AddExpr PLUS MulExpr  */
#line 356 "CminusParser.y"
                                {
					(yyval.symIndex) = emitAddExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1590 "CminusParser.c"
    break;

  case 55: /* AddExpr: AddExpr MINUS MulExpr  */
#line 360 "CminusParser.y"
                                {
					(yyval.symIndex) = emitSubtractExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1598 "CminusParser.c"
    break;

  case 56: /* MulExpr: Factor  */
#line 366 "CminusParser.y"
                                {
					(yyval.symIndex) = (yyvsp[0].symIndex); 
				}
#line 1606 "CminusParser.c"
    break;

  case 57: /* MulExpr: MulExpr TIMES Factor  */
#line 370 "CminusParser.y"
                                {
					(yyval.symIndex) = emitMultiplyExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1614 "CminusParser.c"
    break;

  case 58: /* MulExpr: MulExpr DIVIDE Factor  */
#line 374 "CminusParser.y"
                                {
					(yyval.symIndex) = emitDivideExpression(instList, symtab, (yyvsp[-2].symIndex), (yyvsp[0].symIndex));
				}
#line 1622 "CminusParser.c"
    break;

  case 59: /* Factor: Variable  */
#line 380 "CminusParser.y"
                                { 
					(yyval.symIndex) = emitLoadVariable(instList, symtab, (yyvsp[0].symIndex));
				}
#line 1630 "CminusParser.c"
    break;

  case 60: /* Factor: Constant  */
#line 384 "CminusParser.y"
                                { 
					(yyval.symIndex) = (yyvsp[0].symIndex);
				}
#line 1638 "CminusParser.c"
    break;

  case 61: /* Factor: IDENTIFIER LPAREN RPAREN  */
#line 388 "CminusParser.y"
                                {
					(yyval.symIndex) = SYM_INVALID_INDEX;
					free((yyvsp[-2].name));
				}
#line 1647 "CminusParser.c"
    break;

  case 62: /* Factor: LPAREN Expr RPAREN  */
#line 393 "CminusParser.y"
                                {
					(yyval.symIndex) = (yyvsp[-1].symIndex);
				}
#line 1655 "CminusParser.c"
    break;

  case 63: /* Variable: IDENTIFIER  */
#line 399 "CminusParser.y"
                                {
					int symIndex = SymQueryIndex(symtab, (yyvsp[0].name));
					free((yyvsp[0].name));
					(yyval.symIndex) = emitComputeVariableAddress(instList, symtab, symIndex);
				}
#line 1665 "CminusParser.c"
    break;

  case 64: /* Variable: IDENTIFIER LBRACKET Expr RBRACKET  */
#line 405 "CminusParser.y"
                                {
					int symIndex = SymQueryIndex(symtab, (yyvsp[-3].name));
					free((yyvsp[-3].name));
					(yyval.symIndex) = emitComputeArrayAddress(instList, symtab, symIndex, (yyvsp[-1].symIndex));
				}
#line 1675 "CminusParser.c"
    break;

  case 65: /* StringConstant: STRING  */
#line 413 "CminusParser.y"
                                { 
					int symIndex = SymIndex(symtab, (yyvsp[0].name));
					free((yyvsp[0].name));
					(yyval.symIndex) = emitLoadStringConstantAddress(instList, dataList, symtab, symIndex); 
				}
#line 1685 "CminusParser.c"
    break;

  case 66: /* Constant: INTCON  */
#line 421 "CminusParser.y"
                                { 
					int symIndex = SymIndex(symtab, (yyvsp[0].name));
					free((yyvsp[0].name));
					(yyval.symIndex) = emitLoadIntegerConstant(instList, symtab, symIndex); 
				}
#line 1695 "CminusParser.c"
    break;


#line 1699 "CminusParser.c"

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

#line 427 "CminusParser.y"


/********************C ROUTINES *********************************/

void Cminus_error(char *s) {
	fprintf(stderr, "%s: line %d: %s\n", fileName, Cminus_lineno, s);
}

int Cminus_wrap() {
	return 1;
}

static void initSymTable() {
	symtab = SymInit(SYMTABLE_SIZE); 
	SymInitField(symtab, SYMTAB_OFFSET_FIELD, (Generic) -1, NULL);
	SymInitField(symtab, SYMTAB_REGISTER_INDEX_FIELD, (Generic) -1, NULL);
}

static void deleteSymTable() {
    SymKillField(symtab, SYMTAB_REGISTER_INDEX_FIELD);
    SymKillField(symtab, SYMTAB_OFFSET_FIELD);
    SymKill(symtab);
}

static void initialize(char* inputFileName) {
	stdin = freopen(inputFileName, "r", stdin);
	if (stdin == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", inputFileName);
		exit(-1);
	}

	char* dotChar = rindex(inputFileName, '.');
	int endIndex = strlen(inputFileName) - strlen(dotChar);
	char *sub = substr(inputFileName,0,endIndex);
	char *outputFileName = nssave(2, sub, ".s");
	free(sub);
	stdout = freopen(outputFileName, "w", stdout);
	if (stdout == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", outputFileName);
		free(outputFileName);
		exit(-1);
	} 
	free(outputFileName);

	initSymTable();
	initRegisters();
	instList = dlinkListAlloc(NULL);
	dataList = dlinkListAlloc(NULL);
}

static void finalize() {
    fclose(stdin);
    /*fclose(stdout);*/
    
    deleteSymTable();
 
    cleanupRegisters();
    
    dlinkFreeNodesAndAtoms(instList);
    dlinkFreeNodesAndAtoms(dataList);
	dlinkListFree(instList);
	dlinkListFree(dataList);
	Cminus_lex_destroy();
}

int main(int argc, char** argv) {	
	fileName = argv[1];
	initialize(fileName);
	
    Cminus_parse();
  
  	finalize();
  
  	return 0;
}
/******************END OF C ROUTINES**********************/
