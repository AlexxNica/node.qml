#ifndef BUFFER_H
#define BUFFER_H

#include "../v4integration.h"
#include "../util/qarraydataslice.h"

#include <private/qv4object_p.h>
#include <private/qv4functionobject_p.h>

namespace NodeQml {

enum class BufferEncoding {
    Invalid,
    Ascii,
    Base64,
    Binary,
    Hex,
    Raw,
    Ucs2,
    Utf8,
    Utf16le
};

namespace Heap {

struct Buffer : QV4::Heap::Object {
    Buffer(QV4::ExecutionEngine *v4, size_t length);
    Buffer(QV4::ExecutionEngine *v4, QV4::ArrayObject *array);
    Buffer(QV4::ExecutionEngine *v4, const QByteArray &ba);
    Buffer(QV4::ExecutionEngine *v4, const QTypedArrayDataSlice<char> &slice);
    bool allocateData(size_t length);

    QTypedArrayDataSlice<char> data;
};

struct BufferCtor : QV4::Heap::FunctionObject {
    BufferCtor(QV4::ExecutionContext *scope);
};

} // namespace Heap

struct Buffer : QV4::Object
{
    NODE_V4_OBJECT(Buffer, Object)

    static bool isEqualTo(QV4::Managed *m, QV4::Managed *other);

    static QV4::ReturnedValue getIndexed(QV4::Managed *m, quint32 index, bool *hasProperty);
    static void putIndexed(QV4::Managed *m, uint index, const QV4::Value &value);
    static bool deleteIndexedProperty(QV4::Managed *m, uint index);

    static BufferEncoding parseEncoding(const QString &str);
    static bool isEncoding(const QString &str);
    static int byteLength(const QString &str, BufferEncoding encoding);
    static QByteArray decodeString(const QString &str, BufferEncoding encoding, int limit = -1);
    static QTypedArrayData<char> *fromString(const QByteArray &data);
};

struct BufferCtor : QV4::FunctionObject
{
    NODE_V4_OBJECT(BufferCtor, FunctionObject)

    static QV4::ReturnedValue construct(QV4::Managed *m, QV4::CallData *callData);
    static QV4::ReturnedValue call(QV4::Managed *that, QV4::CallData *callData);

    static QV4::ReturnedValue method_isEncoding(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_isBuffer(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_byteLength(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_concat(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_compare(QV4::CallContext *ctx);
};

struct BufferPrototype : QV4::Object
{
    void init(QV4::ExecutionEngine *v4, QV4::Object *ctor);

    static int compare(const QTypedArrayDataSlice<char> &a, const QTypedArrayDataSlice<char> &b);
    static inline bool checkRange(size_t bufferSize, size_t offset, size_t length = 0);

    static QV4::ReturnedValue method_inspect(QV4::CallContext *ctx);

    static QV4::ReturnedValue method_compare(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_equals(QV4::CallContext *ctx);

    static QV4::ReturnedValue method_write(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_toString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_toJSON(QV4::CallContext *ctx);

    static QV4::ReturnedValue method_copy(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_fill(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_slice(QV4::CallContext *ctx);

    template <typename T, bool LE = true>
    static QV4::ReturnedValue method_readInteger(QV4::CallContext *ctx);

    template <typename T, bool LE = true>
    static QV4::ReturnedValue method_readFloatingPoint(QV4::CallContext *ctx);

    template <typename T, bool LE = true>
    static QV4::ReturnedValue method_writeInteger(QV4::CallContext *ctx);

    template <typename T, bool LE = true>
    static QV4::ReturnedValue method_writeFloatingPoint(QV4::CallContext *ctx);
};

} // namespace NodeQml

#endif // BUFFER_H
