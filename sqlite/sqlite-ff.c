/**
Simon Zolin, 2017 */

#include <sqlite3.h>
#include <sqliteInt.h>

#include <stdlib.h>


extern void sqlite3PagerSetCodec(struct Pager *pPager,
	void *(*xCodec)(void*,void*,Pgno,int),
	void (*xCodecSizeChng)(void*,int,int),
	void (*xCodecFree)(void*),
	void *pCodec);

static void *xCodec(void*,void*,Pgno,int);
static void xCodecSizeChng(void*,int,int);
static void xCodecFree(void*);


const struct sqlite3_codec *giface;

struct codec {
	void *obj;
	const struct sqlite3_codec *iface;
	uint page_size;
};

void sqlite3_codec(sqlite3 *db, const struct sqlite3_codec *codec)
{
	giface = codec;
}

static struct Btree* getBtree(sqlite3 *db, int nDb)
{
	return db->aDb[nDb].pBt;
}

int sqlite3CodecAttach(sqlite3 *db, int nDb, const void *pKey, int nKey)
{
	struct codec *c;
	if (NULL == (c = calloc(1, sizeof(struct codec))))
		return SQLITE_ERROR;
	c->iface = giface;

	if (NULL == (c->obj = c->iface->create(pKey, nKey))) {
		free(c);
		return SQLITE_ERROR;
	}

	sqlite3PagerSetCodec(sqlite3BtreePager(getBtree(db, nDb))
		, &xCodec, &xCodecSizeChng, &xCodecFree, c);
	return SQLITE_OK;
}

void sqlite3CodecGetKey(sqlite3* db, int nDb, void **pKey, int *nKey)
{
	*nKey = 0;
}

static void *xCodec(void *o, void *data, Pgno pgno, int op)
{
	struct codec *c = o;
	return c->iface->process(c->obj, data, pgno, c->page_size, op);
}

static void xCodecSizeChng(void *o, int page_size, int unused)
{
	struct codec *c = o;
	c->page_size = page_size;
}

static void xCodecFree(void *o)
{
	struct codec *c = o;
	c->iface->close(c->obj);
	free(c);
}

int sqlite3_key_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey)
{
	return sqlite3CodecAttach(db, 0, pKey, nKey);
}

int sqlite3_rekey_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey)
{
	return SQLITE_ERROR;
}

void sqlite3_activate_see(const char *info) {}
