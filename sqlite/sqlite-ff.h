/** libsqlite interface for FF.
Simon Zolin, 2017 */

#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif


#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */

#define SQLITE_OK           0   /* Successful result */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */

typedef void (*sqlite3_destructor_type)(void*);
#define SQLITE_STATIC      ((sqlite3_destructor_type)0)


typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;
typedef long long int sqlite3_int64;

#ifdef __cplusplus
extern "C" {
#endif

EXP int sqlite3_close(sqlite3*);
EXP int sqlite3_exec(sqlite3*, const char *sql, int (*callback)(void*,int,char**,char**), void *, char **errmsg);
EXP int sqlite3_changes(sqlite3*);
EXP int sqlite3_open_v2(const char *filename, sqlite3 **ppDb, int flags, const char *zVfs);
EXP int sqlite3_errcode(sqlite3 *db);
EXP const char *sqlite3_errmsg(sqlite3*);
EXP int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail);
EXP int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
EXP int sqlite3_bind_int(sqlite3_stmt*, int, int);
EXP int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
EXP int sqlite3_bind_null(sqlite3_stmt*, int);
EXP int sqlite3_bind_text(sqlite3_stmt*,int,const char*,int,void(*)(void*));
EXP int sqlite3_bind_parameter_count(sqlite3_stmt*);
EXP int sqlite3_clear_bindings(sqlite3_stmt*);
EXP int sqlite3_column_count(sqlite3_stmt *pStmt);
EXP const char *sqlite3_column_name(sqlite3_stmt*, int N);
EXP int sqlite3_step(sqlite3_stmt*);
EXP int sqlite3_column_bytes(sqlite3_stmt*, int iCol);
EXP int sqlite3_column_int(sqlite3_stmt*, int iCol);
EXP sqlite3_int64 sqlite3_column_int64(sqlite3_stmt*, int iCol);
EXP const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
EXP int sqlite3_column_type(sqlite3_stmt*, int iCol);
EXP int sqlite3_finalize(sqlite3_stmt *pStmt);
EXP int sqlite3_reset(sqlite3_stmt *pStmt);

#ifdef __cplusplus
}
#endif

#undef EXP
