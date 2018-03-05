/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of a Qt Solutions component.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#ifndef QTSOAP_H
#define QTSOAP_H
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtXml/QtXml>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QUrl>
#include <QtCore/QHash>
#include <QtCore/QLinkedList>

#include <memory>

#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#if defined(QtSOAP_EXPORTS)
#define QT_QTSOAP_EXPORT Q_DECL_EXPORT
#else
#define QT_QTSOAP_EXPORT Q_DECL_IMPORT
#endif
#endif

#if !defined(QT_QTSOAP_EXPORT)
#define QT_QTSOAP_EXPORT Q_DECL_EXPORT
#endif

#define SOAPv11_ENVELOPE "http://schemas.xmlsoap.org/soap/envelope/"
#define SOAPv11_ENCODING "http://schemas.xmlsoap.org/soap/encoding/"
#define SOAPv11_ACTORNEXT "http://schemas.xmlsoap.org/soap/actor/next"

#define XML_SCHEMA "http://www.w3.org/1999/XMLSchema"
#define XML_SCHEMA_INSTANCE "http://www.w3.org/1999/XMLSchema-instance"
#define XML_NAMESPACE "http://www.w3.org/XML/1998/namespace"

class QT_QTSOAP_EXPORT QtSoapQName
{
public:
    QtSoapQName(const QString &name = QString::QString(), const QString &uri = QString::QString());
    ~QtSoapQName();

    QtSoapQName &operator=(const QString &s);

    QString name() const;
    QString uri() const;

private:
    QString n;
    QString nuri;
};

bool operator==(const QtSoapQName &n1, const QtSoapQName &n2);
bool operator<(const QtSoapQName &n1, const QtSoapQName &n2);

class QT_QTSOAP_EXPORT QtSoapType
{
public:
    enum Type
    {
        Duration,
        DateTime,
        Time,
        Date,
        GYearMonth,
        GYear,
        GMonthDay,
        GDay,
        GMonth,
        Boolean,
        Base64Binary,
        HexBinary,
        Float,
        Double,
        AnyURI,
        QName,
        NOTATION,
        String,
        NormalizedString,
        Token,
        Language,
        Name,
        NMTOKEN,
        NCName,
        ID,
        IDREF,
        ENTITY,
        Decimal,
        Integer,
        NonPositiveInteger,
        NegativeInteger,
        Long,
        Int,
        Short,
        Byte,
        NonNegativeInteger,
        UnsignedLong,
        PositiveInteger,
        UnsignedInt,
        UnsignedShort,
        UnsignedByte,
        Array,
        Struct,
        Other
    };

    QtSoapType();
    QtSoapType(const QtSoapQName &name, Type t = Other);
    QtSoapType(const QtSoapType &copy);
    QtSoapType &operator=(const QtSoapType &copy);
    virtual ~QtSoapType();

    virtual void clear();

    virtual bool parse(QDomNode);
    virtual bool isValid() const;

    virtual int count() const;
    virtual QVariant value() const;

    virtual QtSoapType &operator[](int);
    virtual QtSoapType &operator[](const QtSoapQName &s);
    virtual QtSoapType &operator[](const QString &name);

    virtual const QtSoapType &operator[](int) const;
    virtual const QtSoapType &operator[](const QtSoapQName &s) const;
    virtual const QtSoapType &operator[](const QString &name) const;

    virtual QDomElement toDomElement(QDomDocument) const;

    virtual Type type() const;
    virtual QString id() const;
    virtual QString href() const;
    virtual QString typeName() const;
    virtual QtSoapQName name() const;

    virtual QString toString() const;
    virtual int toInt() const;
    virtual bool toBool() const;

    void setName(const QtSoapQName &);
    void setId(const QString &);
    void setHref(const QString &);

    QString errorString() const;

    static QString typeToName(QtSoapType::Type t);
    static Type nameToType(const QString &);

protected:
    Type t;
    QString errorStr;
    QString i;
    QtSoapQName n;
    QString u;
    QString h;
};

class QtSoapArrayIterator;

class QT_QTSOAP_EXPORT QtSoapArray : public QtSoapType
{
public:
    QtSoapArray();
    QtSoapArray(const QtSoapQName &name, QtSoapType::Type type = Other, int size0 = -1,
                int size1 = -1, int size2 = -1, int size3 = -1, int size4 = -1);
    QtSoapArray(const QtSoapArray &copy);
    QtSoapArray &operator=(const QtSoapArray &copy);
    ~QtSoapArray();

    void clear();

    bool parse(QDomNode node);
    bool isValid() const;

    int count() const;

    QtSoapType &at(int pos0);
    QtSoapType &at(int pos0, int pos1);
    QtSoapType &at(int pos0, int pos1, int pos2);
    QtSoapType &at(int pos0, int pos1, int pos2, int pos3);
    QtSoapType &at(int pos0, int pos1, int pos2, int pos3, int pos4);
    QtSoapType &operator[](int i);
    QtSoapType &operator[](const QString &);
    QtSoapType &operator[](const QtSoapQName &);

    const QtSoapType &at(int pos) const;
    const QtSoapType &at(int pos0, int pos1) const;
    const QtSoapType &at(int pos0, int pos1, int pos2) const;
    const QtSoapType &at(int pos0, int pos1, int pos2, int pos3) const;
    const QtSoapType &at(int pos0, int pos1, int pos2, int pos3, int pos4) const;
    const QtSoapType &operator[](int i) const;
    const QtSoapType &operator[](const QString &) const;
    const QtSoapType &operator[](const QtSoapQName &) const;

    void append(std::shared_ptr<QtSoapType> item);
    void insert(int pos0, std::shared_ptr<QtSoapType> item);
    void insert(int pos0, int pos1, std::shared_ptr<QtSoapType> item);
    void insert(int pos0, int pos1, int pos2, std::shared_ptr<QtSoapType> item);
    void insert(int pos0, int pos1, int pos2, int pos3, std::shared_ptr<QtSoapType> item);
    void insert(int pos0, int pos1, int pos2, int pos3, int pos4, std::shared_ptr<QtSoapType> item);

    QDomElement toDomElement(QDomDocument doc) const;

    friend class QtSoapArrayIterator;

protected:
    QString arraySizeString() const;
    QString arrayTypeString() const;

    QHash<int, std::shared_ptr<QtSoapType>> array;
    int lastIndex;

private:
    Type arrayType;
    int order;
    int siz0, siz1, siz2, siz3, siz4;
};

class QT_QTSOAP_EXPORT QtSoapArrayIterator
{
public:
    QtSoapArrayIterator(QtSoapArray &);
    QtSoapArrayIterator(const QtSoapArrayIterator &copy);
    QtSoapArrayIterator &operator=(const QtSoapArrayIterator &j);
    ~QtSoapArrayIterator();

    int pos() const;
    void pos(int *pos0, int *pos1 = 0, int *pos2 = 0, int *pos3 = 0, int *pos4 = 0) const;

    std::shared_ptr<QtSoapType> data();
    const std::shared_ptr<QtSoapType> current() const;

    void operator++();
    bool operator!=(const QtSoapArrayIterator &j) const;
    bool operator==(const QtSoapArrayIterator &j) const;

    bool atEnd() const;

private:
    QHash<int, std::shared_ptr<QtSoapType>>::Iterator it;
    QtSoapArray *arr;
};

class QtSoapStructIterator;

class QT_QTSOAP_EXPORT QtSoapStruct : public QtSoapType
{
public:
    QtSoapStruct();
    QtSoapStruct(const QtSoapQName &name);
    QtSoapStruct(const QtSoapStruct &copy);
    QtSoapStruct &operator=(const QtSoapStruct &copy);
    ~QtSoapStruct();

    void clear();

    bool parse(QDomNode node);
    bool isValid() const;

    int count() const;

    QtSoapType &at(const QtSoapQName &key);
    const QtSoapType &at(const QtSoapQName &key) const;

    QtSoapType &operator[](int);
    QtSoapType &operator[](const QtSoapQName &key);
    QtSoapType &operator[](const QString &key);

    const QtSoapType &operator[](int) const;
    const QtSoapType &operator[](const QtSoapQName &key) const;
    const QtSoapType &operator[](const QString &key) const;

    void insert(std::shared_ptr<QtSoapType> item);

    QDomElement toDomElement(QDomDocument doc) const;

    friend class QtSoapStructIterator;

protected:
    QList<std::shared_ptr<QtSoapType>> dict;
};

class QT_QTSOAP_EXPORT QtSoapStructIterator
{
public:
    QtSoapStructIterator(QtSoapStruct const &);
    ~QtSoapStructIterator();

    QtSoapQName key() const;
    std::shared_ptr<QtSoapType> data();
    const std::shared_ptr<QtSoapType> current() const;

    void operator++();
    bool operator!=(const QtSoapStructIterator &j) const;
    bool operator==(const QtSoapStructIterator &j) const;

private:
    QList<std::shared_ptr<QtSoapType>>::const_iterator it;
    QList<std::shared_ptr<QtSoapType>>::const_iterator itEnd;
};

class QT_QTSOAP_EXPORT QtSoapSimpleType : public QtSoapType
{
public:
    QtSoapSimpleType();
    QtSoapSimpleType(const QtSoapQName &name);
    QtSoapSimpleType(const QtSoapQName &name, int n);
    QtSoapSimpleType(const QtSoapQName &name, bool n, int dummy);
    QtSoapSimpleType(const QtSoapQName &name, const QString &n);
    QtSoapSimpleType(const QtSoapSimpleType &copy);
    QtSoapSimpleType &operator=(const QtSoapSimpleType &copy);
    ~QtSoapSimpleType();

    void clear();

    bool parse(QDomNode node);
    bool isValid() const;

    QString toString() const;
    int toInt() const;
    bool toBool() const;
    QVariant value() const;

    QDomElement toDomElement(QDomDocument doc) const;

protected:
    QVariant v;
};

class QT_QTSOAP_EXPORT QtSoapMessage
{
    friend class QtSoapHttpServer;

public:
    QtSoapMessage();
    QtSoapMessage(const QtSoapMessage &copy);
    ~QtSoapMessage();

    QtSoapMessage &operator=(const QtSoapMessage &copy);

    bool setContent(const QByteArray &buffer);
    bool setContent(QDomDocument &d);

    void addBodyItem(std::shared_ptr<QtSoapType>);
    void addHeaderItem(std::shared_ptr<QtSoapType>);

    // Method and response
    const QtSoapType &method() const;
    const QtSoapType &returnValue() const;
    void setMethod(const QtSoapQName &);
    void setMethod(const QString &name, const QString &url = QString::QString());
    void addMethodArgument(std::shared_ptr<QtSoapType>);
    void addMethodArgument(const QString &uri, const QString &name, const QString &value);
    void addMethodArgument(const QString &uri, const QString &name, bool value, int dummy);
    void addMethodArgument(const QString &uri, const QString &name, int value);

    // Fault
    enum FaultCode
    {
        VersionMismatch,
        MustUnderstand,
        Client,
        Server,
        Other
    };

    bool isFault() const;
    FaultCode faultCode() const;
    const QtSoapType &faultString() const;
    const QtSoapType &faultDetail() const;
    void setFaultCode(FaultCode code);
    void setFaultString(const QString &fstring);
    void addFaultDetail(std::shared_ptr<QtSoapType> detail);

    // additional method for setting further namespaces
    void useNamespace(const QString &prefix, const QString &namespaceURI);

    // Generating
    void clear();
    QString toXmlString(int indent = 0) const;

    // Errors
    QString errorString() const;

protected:
    enum MessageType
    {
        Fault,
        MethodRequest,
        MethodResponse,
        OtherType
    };

    bool isValidSoapMessage(const QDomDocument &candidate);

    QtSoapStruct &body() const;
    QtSoapStruct &header() const;

    void init();

private:
    MessageType type;

    mutable QtSoapStruct envelope;

    QtSoapQName m;
    QtSoapStruct margs;

    QString errorStr;

    QString externalNamespacePrefix;
    QString externalNamespaceURI;
};

class QT_QTSOAP_EXPORT QtSoapTypeConstructorBase
{
public:
    inline QtSoapTypeConstructorBase() {}

    virtual inline ~QtSoapTypeConstructorBase() {}

    virtual std::shared_ptr<QtSoapType> createObject(QDomNode) = 0;

    virtual QString errorString() const = 0;
};

template <class T>
class QT_QTSOAP_EXPORT QtSoapTypeConstructor : public QtSoapTypeConstructorBase
{
public:
    QtSoapTypeConstructor() {}

    std::shared_ptr<QtSoapType> createObject(QDomNode node) Q_DECL_OVERRIDE
    {
        auto t = std::make_shared<T>();
        if (t->parse(node)) {
            return t;
        } else {
            errorStr = t->errorString();
            return nullptr;
        }
    }

    QString errorString() const { return errorStr; }

private:
    mutable QString errorStr;
};

class QT_QTSOAP_EXPORT QtSoapTypeFactory
{
private:
    QtSoapTypeFactory();

public:
    ~QtSoapTypeFactory();

    static QtSoapTypeFactory &instance();

    bool registerHandler(const QString &name, QtSoapTypeConstructorBase *handler);

    std::shared_ptr<QtSoapType> soapType(QDomNode node) const;

    QString errorString() const;

private:
    mutable QString errorStr;
    QHash<QString, QtSoapTypeConstructorBase *> typeHandlers;
    QLinkedList<QtSoapTypeConstructorBase *> deleteList;
};

class QT_QTSOAP_EXPORT QtSoapNamespaces
{
public:
    void registerNamespace(const QString &prefix, const QString &uri);
    QString prefixFor(const QString &ns);

    static QtSoapNamespaces &instance();

private:
    QMap<QString, QString> namespaces;
    QtSoapNamespaces();
};

class QT_QTSOAP_EXPORT QtSoapHttpTransport : public QObject
{
    Q_OBJECT

public:
    QtSoapHttpTransport(QObject *parent = 0);
    ~QtSoapHttpTransport();

    void setHost(const QString &host, bool useSecureHTTP = false, int port = 0);
    void setHost(const QString &host, int port); // obsolete
    void setAction(const QString &action);
    void submitRequest(QNetworkRequest &networkReq, QtSoapMessage &request, const QString &path);
    void submitRequest(QtSoapMessage &request, const QString &path);
    const QtSoapMessage &getResponse() const;

    QNetworkAccessManager *networkAccessManager();
    QNetworkReply *networkReply();

Q_SIGNALS:
    void responseReady();
    void responseReady(const QtSoapMessage &response);

private Q_SLOTS:
    void readResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager networkMgr;
    QPointer<QNetworkReply> networkRep;
    QUrl url;
    QString soapAction;
    QtSoapMessage soapResponse;
};

#endif
