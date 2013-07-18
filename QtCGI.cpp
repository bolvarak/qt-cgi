///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \author Travis Brown <tmbrown6@gmail.com> ////////////////////////////////////////////////////////////////////////
/// \version 1.0                              ///////////////////////////////////////////////////////////////////////
/// \title QtCGI                              //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QtCGI.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QtCGI*    QtCGI::mInstance               = NULL;
QString QtCGI::ContentImageGIF           = "image/gif";
QString QtCGI::ContentImageJPEG          = "image/jpeg";
QString QtCGI::ContentImageJPG           = "image/jpg";
QString QtCGI::ContentImagePNG           = "image/png";
QString QtCGI::ContentImageSVG           = "image/svg+xml";
QString QtCGI::ContentImageTIFF          = "image/tiff";
QString QtCGI::ContentFont               = "application/font";
QString QtCGI::ContentFontEOT            = "application/vnd.ms-fontobject";
QString QtCGI::ContentFontOTF            = "font/opentype";
QString QtCGI::ContentFontTTF            = "font/ttf";
QString QtCGI::ContentFontWOFF           = "font/woff";
QString QtCGI::ContentScriptECMAS        = "text/ecmascript";
QString QtCGI::ContentScriptVB           = "text/vbscript";
QString QtCGI::ContentTypeCSS            = "text/css";
QString QtCGI::ContentTypeHTML           = "text/html";
QString QtCGI::ContentTypeJS             = "text/javascript";
QString QtCGI::ContentTypeJSON           = "application/json";
QString QtCGI::ContentTypeText           = "text/plain";
QString QtCGI::ContentTypeXML            = "text/xml";
QString QtCGI::HeaderComSpec             = "COMSPEC";
QString QtCGI::HeaderDocumentRoot        = "DOCUMENT_ROOT";
QString QtCGI::HeaderGatewayInterface    = "GATEWAY_INTERFACE";
QString QtCGI::HeaderHttpAccept          = "HTTP_ACCEPT";
QString QtCGI::HeaderHttpAcceptEncoding  = "HTTP_ACCEPT_ENCODING";
QString QtCGI::HeaderHttpAcceptLanguage  = "HTTP_ACCEPT_LANGUAGE";
QString QtCGI::HeaderHttpConnection      = "HTTP_CONNECTION";
QString QtCGI::HeaderHttpCookie          = "HTTP_COOKIE";
QString QtCGI::HeaderHttpHost            = "HTTP_HOST";
QString QtCGI::HeaderHttpUserAgent       = "HTTP_USER_AGENT";
QString QtCGI::HeaderPath                = "PATH";
QString QtCGI::HeaderQueryString         = "QUERY_STRING";
QString QtCGI::HeaderRemoteAddress       = "REMOTE_ADDR";
QString QtCGI::HeaderRemotePort          = "REMOTE_PORT";
QString QtCGI::HeaderRequestMethod       = "REQUEST_METHOD";
QString QtCGI::HeaderRequestUri          = "REQUEST_URI";
QString QtCGI::HeaderScriptFilename      = "SCRIPT_FILENAME";
QString QtCGI::HeaderScriptName          = "SCRIPT_NAME";
QString QtCGI::HeaderServerAddress       = "SERVER_ADDR";
QString QtCGI::HeaderServerAdministrator = "SERVER_ADMIN";
QString QtCGI::HeaderServerName          = "SERVER_NAME";
QString QtCGI::HeaderServerPort          = "SERVER_PORT";
QString QtCGI::HeaderServerProtocol      = "SERVER_PROTOCOL";
QString QtCGI::HeaderServerSignature     = "SERVER_SIGNATURE";
QString QtCGI::HeaderServerSoftware      = "SERVER_SOFTWARE";
QString QtCGI::MethodDelete              = "DELETE";
QString QtCGI::MethodGet                 = "GET";
QString QtCGI::MethodHead                = "HEAD";
QString QtCGI::MethodPost                = "POST";
QString QtCGI::MethodPut                 = "PUT";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method maintains access to the singleton instance of this class
 * @brief QtCGI::Instance()
 * @param bool bReset [false]
 * @param QObject* qoParent [0]
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::Instance(bool bReset, QObject* qoParent)
{
  // Check for an existing instance or a reset notification
	if ((mInstance == NULL) || (bReset == true)) {
		// Create a new instance
		mInstance = new QtCGI(qoParent);
	}
	// Return the instance
	return mInstance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This constructor sets up the class to read the HTTP headers and interact with the QtCGI
 * @brief QtCGI::QtCGI()
 * @param QObject* qoParent [0]
 */
QtCGI::QtCGI(QObject* qoParent) : QObject(qoParent)
{
	// Process the request and return
	this->ProcessHeaders() // Headers
		->ProcessCookies()   // Cookies
		->ProcessGet()       // Query String
		->ProcessPost();     // POST data
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method processes the cookies into the instance
 * @brief QtCGI::ProcessCookies()
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::ProcessCookies()
{
	// Load the cookies
	QString strCookies = this->mRequestHeaders.value(QtCGI::HeaderHttpCookie);
	// Check for cookies
	if (!strCookies.isEmpty()) {
		// Set the cookies into the instance
		this->mCookies = this->DecodeQuery(strCookies, ";");
	}
	// Return the instance
	return this;
}

/**
 * @paragraph This method processes the QUERY_STRING into the instance
 * @brief QtCGI::ProcessGet()
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::ProcessGet()
{
	// Load the Query String
	QString strQuery = this->mRequestHeaders.value(QtCGI::HeaderQueryString);
	// Check for a query string
	if (!strQuery.isEmpty()) {
		// Set the GET variables into the instance
		this->mGetParameters = this->DecodeQuery(strQuery);
	}
	// Return the instance
	return this;
}

/**
 * @paragraph This method processes the request headers into the instance
 * @brief QtCGI::ProcessHeaders()
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::ProcessHeaders()
{
	// Add the DOCUMENT_ROOT header
	this->mRequestHeaders.insert(QtCGI::HeaderDocumentRoot,        QString(qgetenv(QtCGI::HeaderDocumentRoot.toLatin1().data())));
	// Add the GATEWAY_INTERFACE header
	this->mRequestHeaders.insert(QtCGI::HeaderGatewayInterface,    QString(qgetenv(QtCGI::HeaderGatewayInterface.toLatin1().data())));
	// Add the HTTP_ACCEPT header
	this->mRequestHeaders.insert(QtCGI::HeaderHttpAccept,          QString(qgetenv(QtCGI::HeaderHttpAccept.toLatin1().data())));
	// Add the HTTP_ACCEPT_ENCODING header
	this->mRequestHeaders.insert(QtCGI::HeaderHttpAcceptEncoding,  QString(qgetenv(QtCGI::HeaderHttpAcceptEncoding.toLatin1().data())));
	// Add the HTTP_ACCEPT_LANGUAGE header
	this->mRequestHeaders.insert(QtCGI::HeaderHttpAcceptLanguage,  QString(qgetenv(QtCGI::HeaderHttpAcceptLanguage.toLatin1().data())));
	// Add the HTTP_CONNECTION header
	this->mRequestHeaders.insert(QtCGI::HeaderHttpConnection,      QString(qgetenv(QtCGI::HeaderHttpConnection.toLatin1().data())));
	// Add the HTTP_COOKIE header
	this->mRequestHeaders.insert(QtCGI::HeaderHttpCookie,          QString(qgetenv(QtCGI::HeaderHttpCookie.toLatin1().data())));
	// Add the HTTP_HOST header
	this->mRequestHeaders.insert(QtCGI::HeaderHttpHost,            QString(qgetenv(QtCGI::HeaderHttpHost.toLatin1().data())));
	// Add the HTTP_USER_AGENT header
	this->mRequestHeaders.insert(QtCGI::HeaderHttpUserAgent,       QString(qgetenv(QtCGI::HeaderHttpUserAgent.toLatin1().data())));
	// Add the PATH header
	this->mRequestHeaders.insert(QtCGI::HeaderPath,                QString(qgetenv(QtCGI::HeaderPath.toLatin1().data())));
	// Add the QUERY_STRING header
	this->mRequestHeaders.insert(QtCGI::HeaderQueryString,         QString(qgetenv(QtCGI::HeaderQueryString.toLatin1().data())));
	// Add the REMOTE_ADDR header
	this->mRequestHeaders.insert(QtCGI::HeaderRemoteAddress,       QString(getenv(QtCGI::HeaderRemoteAddress.toLatin1().data())));
	// Add the REMOTE_PORT header
	this->mRequestHeaders.insert(QtCGI::HeaderRemotePort,          QString(qgetenv(QtCGI::HeaderRemotePort.toLatin1().data())));
	// Add the REQUEST_METHOD header
	this->mRequestHeaders.insert(QtCGI::HeaderRequestMethod,       QString(qgetenv(QtCGI::HeaderRequestMethod.toUpper().toLatin1().data())));
	// Add the REQUEST_URI header
	this->mRequestHeaders.insert(QtCGI::HeaderRequestUri,          QString(qgetenv(QtCGI::HeaderRequestUri.toLatin1().data())));
	// Add the SCRIPT_FILENAME header
	this->mRequestHeaders.insert(QtCGI::HeaderScriptFilename,      QString(qgetenv(QtCGI::HeaderScriptFilename.toLatin1().data())));
	// Add the SCRIPT_NAME header
	this->mRequestHeaders.insert(QtCGI::HeaderScriptName,          QString(qgetenv(QtCGI::HeaderScriptName.toLatin1().data())));
	// Add the SERVER_ADDR header
	this->mRequestHeaders.insert(QtCGI::HeaderServerAddress,       QString(qgetenv(QtCGI::HeaderServerAddress.toLatin1().data())));
	// Add the SERVER_ADMIN header
	this->mRequestHeaders.insert(QtCGI::HeaderServerAdministrator, QString(qgetenv(QtCGI::HeaderServerAdministrator.toLatin1().data())));
	// Add the SERVER_NAME header
	this->mRequestHeaders.insert(QtCGI::HeaderServerName,          QString(qgetenv(QtCGI::HeaderServerName.toLatin1().data())));
	// Add the SERVER_PORT header
	this->mRequestHeaders.insert(QtCGI::HeaderServerPort,          QString(qgetenv(QtCGI::HeaderServerPort.toLatin1().data())));
	// Add the SERVER_PROTOCOL header
	this->mRequestHeaders.insert(QtCGI::HeaderServerProtocol,      QString(qgetenv(QtCGI::HeaderServerProtocol.toLatin1().data())));
	// Add the SERVER_SIGNATURE header
	this->mRequestHeaders.insert(QtCGI::HeaderServerSignature,     QString(qgetenv(QtCGI::HeaderServerSignature.toLatin1().data())));
	// Add the SERVER_SOFTWARE header
	this->mRequestHeaders.insert(QtCGI::HeaderServerSoftware,      QString(qgetenv(QtCGI::HeaderServerSoftware.toLatin1().data())));
	// Return the instance
	return this;
}

/**
 * @paragraph This method processes the POST data into the instance
 * @brief QtCGI::ProcessPost()
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::ProcessPost()
{
	// Make sure this is a POST request
	if (this->mRequestHeaders.value(QtCGI::HeaderRequestMethod).toUpper() == QtCGI::MethodPost) {
		// Create the post data placeholder
		std::string strPostData;
		// Loop throug the POST lines
		std::getline(std::cin, strPostData);
		// Make sure we don't have an empty POST set
		if (!QString::fromStdString(strPostData).isEmpty()) {
			// Set the POST data into the instance
			this->DecodeQuery(QString().fromStdString(strPostData));
		}
	}
	// Return the instance
	return this;
}

/**
 * @paragraph This method writes the content body to the browser/socket/stream
 * @brief QtCGI::SendContent()
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::SendContent()
{
	// Write the content
	std::cout << this->mContent.toStdString() << std::endl;
	// Return the instance
	return this;
}

/**
 * @paragraph This method writes the response headers to the browser/socket/stream
 * @brief QtCGI::SendHeaders()
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::SendHeaders()
{
	// Add the content length header
	this->AddResponseHeader("Content-Length", QString::number(this->mContent.length()));
	// Create the iterator
	QMap<QString, QString>::iterator itrHeaders;
	// Loop through the headers
	for (itrHeaders = this->mResponseHeaders.begin(); itrHeaders != this->mResponseHeaders.end(); ++itrHeaders) {
		// Print the header
		std::cout << itrHeaders.key().toStdString() << ": " << itrHeaders.value().toStdString() << "\r\n";
	}
	// Send an extra newline
	std::cout << "\r\n";
	// Return the instance
	return this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method sets a response header into the instance
 * @brief QtCGI::AddResponseHeader()
 * @param QString strName
 * @param QString strValue
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::AddResponseHeader(QString strName, QString strValue)
{
	// Set the response header into the instance
	this->mResponseHeaders.insert(strName, strValue);
	// Return the instance
	return this;
}

/**
 * @paragraph This method decodes a query string into a query map
 * @brief QtCGI::DecodeQuery()
 * @param QString strQuery
 * @param QString strPairSeparator ["&"]
 * @return QMap<QString, QString>
 */
QMap<QString, QString> QtCGI::DecodeQuery(QString strQuery, QString strPairSeparator)
{
	// Create the map placeholder
	QMap<QString, QString> qmQuery;
	// Split the parameters
	QStringList qslParameters = strQuery.split(strPairSeparator);
	// Loop through the parameters
	foreach (QString strPair, qslParameters) {
		// Split the key/value pair
		QStringList qslPair = strPair.split("=");
		// Set the pair into the map
		qmQuery.insert(QUrl::fromPercentEncoding(qslPair.at(0).toLatin1()).replace("+", " "), QUrl::fromPercentEncoding(qslPair.at(1).toLatin1()).replace("+", " "));
	}
	// Return the map
	return qmQuery;
}

/**
 * @paragraph This method converts a query map into a query string
 * @brief QtCGI::EncodeQuery()
 * @param QMap<QString, QString> qmQuery
 * @param QString strPairGlue ["&"]
 * @return QString
 */
QString QtCGI::EncodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue)
{
	// Create the query placeholder
	QStringList qslQuery;
	// Loop through the parameters
	foreach (QString strKey, qmQuery) {
		// Create the pair list
		QStringList qslPair;
		// Add the key
		qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
		// Add the value
		qslPair.append(QString(QUrl::toPercentEncoding(qmQuery.value(strKey))).replace(" ", "+"));
		// Append the pair to the query string
		qslQuery.append(qslPair.join("="));
	}
	// Return the query string
	return qslQuery.join(strPairGlue);
}

/**
 * @paragraph This method converts a query variant map into a query string
 * @brief QtCGI::EncodeQuery()
 * @param QVariantMap qvmQuery
 * @param QString strPairGlue ["&"]
 * @return QString
 */
QString QtCGI::EncodeQuery(QVariantMap qvmQuery, QString strPairGlue)
{
	// Create the query placeholder
	QStringList qslQuery;
	// Loop through the parameters
	foreach (QString strKey, qvmQuery.keys()) {
		// Create the pair list
		QStringList qslPair;
		// Add the keyt
		qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
		// Add the valie
		qslPair.append(QString(QUrl::toPercentEncoding(qvmQuery.value(strKey).toString())).replace(" ", "+"));
		// Append the pair to the query string
		qslQuery.append(qslPair.join("="));
	}
	// Return the query string
	return qslQuery.join(strPairGlue);
}

/**
 * @paragraph This method writes the response to the browser/socket/stram
 * @brief QtCGI::WriteResponse()
 * @return void
 */
void QtCGI::WriteResponse()
{
	// Write the data to the requester
	this->SendHeaders()  // Headers
		->SendContent(); // Content
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method returns the current content from the instance
 * @brief QtCGI::GetContent()
 * @return QString QtCGI::mContent
 */
QString QtCGI::GetContent()
{
	// Return the content from the instance
	return this->mContent;
}

/**
 * @paragraph This method returns a cookies from the instance if it exists
 * @brief QtCGI::GetCookie()
 * @param QString strName
 * @return QString
 */
QString QtCGI::GetCookie(QString strName)
{
	// Check for the cookie
	if (this->mCookies.contains(strName)) {
		// Return the cookie
		return this->mCookies.value(strName);
	}
	// Elsewise, return null
	return NULL;
}

/**
 * @paragraph This method returns the current cookie map from the instance
 * @brief QtCGI::GetCookies()
 * @return QMap<QString, QString> QtCGI::mCookies
 */
QMap<QString, QString> QtCGI::GetCookies()
{
	// Return the current cookie map
	return this->mCookies;
}

/**
 * @paragraph This method returns a GET/POST parameter from the instance if it exists
 * @brief QtCGI::GetParam()
 * @param QString strName
 * @return QString
 */
QString QtCGI::GetParam(QString strName)
{
	// Check for the parameter in POST
	if (this->mPostParameters.contains(strName)) {
		// Return the POST parameter
		return this->mPostParameters.value(strName);
	}
	// Check for the parameter in GET
	if (this->mGetParameters.contains(strName)) {
		// Return the GET parameter
		return this->mGetParameters.value(strName);
	}
	// Elsewise, return null
	return NULL;
}

/**
 * @paragraph This method returns the current POST map from the instance
 * @brief QtCGI::GetPostData()
 * @return QMap<QString, QString> QtCGI::mPostParameters
 */
QMap<QString, QString> QtCGI::GetPostData()
{
	// Return the POST data
	return this->mPostParameters;
}

/**
 * @paragraph This method returns the current GET map from the instance
 * @brief QtCGI::GetQueryData()
 * @return QMap<QString, QString> QtCGI::mGetParameters
 */
QMap<QString, QString> QtCGI::GetQueryData()
{
	// Return the GET data
	return this->mGetParameters;
}

/**
 * @paragraph This method returns a request header from the instance if it exists
 * @brief QtCGI::GetRequestHeader()
 * @param QString strName
 * @return QString
 */
QString QtCGI::GetRequestHeader(QString strName)
{
	// Check to see if the request header exists
	if (this->mRequestHeaders.contains(strName)) {
		// Return the request header
		return this->mRequestHeaders.value(strName);
	}
	// Elsewise, return null
	return NULL;
}

/**
 * @paragraph This method returns the current request headers from the instance
 * @brief QtCGI::GetRequestHeaders()
 * @return QMap<QString, QString> QtCGI::mRequestHeaders
 */
QMap<QString, QString> QtCGI::GetRequestHeaders()
{
	// Return the response headers
	return this->mRequestHeaders;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method sets the response content into the instance
 * @brief QtCGI::SetContent()
 * @param QString strContent
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::SetContent(QString strContent)
{
	// Set the contnt into the instance
	this->mContent = strContent;
	// Return the instane
	return this;
}

/**
 * @paragraph This method sets the content type header into the instance
 * @brief QtCGI::SetContentType()
 * @param QString strContentType
 * @return QtCGI* QtCGI::mInstance
 */
QtCGI* QtCGI::SetContentType(QString strContentType)
{
	// Set the content type into the instance
	this->AddResponseHeader("Content-Type", strContentType);
	// Return the instance
	return this;
}
