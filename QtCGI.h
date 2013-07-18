///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \author Travis Brown <tmbrown6@gmail.com> ////////////////////////////////////////////////////////////////////////
/// \version 1.0                              ///////////////////////////////////////////////////////////////////////
/// \title QtCGI                              //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef QtCGI_H
#define QtCGI_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <QByteArray>
#include <QDebug>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QVariant>
#include <QVariantMap>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// QtCGI Class Definition /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This class handles the interaction between the web browser and the application
 * @brief QtCGI
 */
class QtCGI : public QObject
{
  	/**
		 * Ensure this class is recognized by Qt
		 */
		Q_OBJECT

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods & Properties ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief QtCGI::mInstance
		 * @var QtCGI*
		 */
		static QtCGI* mInstance;

		/**
		 * @paragraph This property contains the response content
		 * @brief QtCGI::mContent
		 * @var QString
		 */
		QString mContent;

		/**
		 * @paragraph This property contains the HTTP cookies
		 * @brief QtCGI::mCookies
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mCookies;

		/**
		 * @paragraph This property contains the GET data
		 * @brief QtCGI::mGetParameters
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mGetParameters;

		/**
		 * @paragraph This property contains the POST data
		 * @brief QtCGI::mPostParameters
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mPostParameters;

		/**
		 * @paragraph This property contains the request headers from the client
		 * @brief QtCGI::mRequestHeaders
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mRequestHeaders;

		/**
		 * @paragraph This property contains the response headers to send to the client
		 * @brief QtCGI::mResponseHeaders
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mResponseHeaders;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method processes the HTTP_COOKIE from the header
		 * @brief QtCGI::ProcessCookies()
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* ProcessCookies();

		/**
		 * @paragraph This method processes the QUERY_STRING from the header
		 * @brief QtCGI::ProcessGet()
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* ProcessGet();

		/**
		 * @paragraph This method processes the request headers into the instance
		 * @brief QtCGI::ProcessHeaders()
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* ProcessHeaders();

		/**
		 * @paragraph This method processes the POST data into the instance
		 * @brief QtCGI::ProcessPost()
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* ProcessPost();

		/**
		 * @paragraph This method writes the content to the browser/socket/stream
		 * @brief QtCGI::SendContent()
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* SendContent();

		/**
		 * @paragraph This method writes the response headers to the browser/socket/stream
		 * @brief QtCGI::SendHeaders()
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* SendHeaders();

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the header type for GIF
		 * @brief QtCGI::ContentImageGIF
		 * @var QString
		 */
		static QString ContentImageGIF;

		/**
		 * @paragraph This property contains the header type for JPEG
		 * @brief QtCGI::ContentImageJPEG
		 * @var QString
		 */
		static QString ContentImageJPEG;

		/**
		 * @paragraph This property contains the header type for JPG
		 * @brief QtCGI::ContentImageJPG
		 * @var QString
		 */
		static QString ContentImageJPG;

		/**
		 * @paragraph This property contains the header type for PNG
		 * @brief QtCGI::ContentImagePNG
		 * @var QString
		 */
		static QString ContentImagePNG;

		/**
		 * @paragraph Thie property contains the header type for SVG
		 * @brief QtCGI::ContentImageSVG
		 * @var QString
		 */
		static QString ContentImageSVG;

		/**
		 * @paragraph This property contains the header type for TIFF
		 * @brief QtCGI::ContentImageTIFF
		 * @var QString
		 */
		static QString ContentImageTIFF;

		/**
		 * @paragraph This property contins the header type for FONT
		 * @brief QtCGI::ContentFont
		 * @var QString
		 */
		static QString ContentFont;

		/**
		 * @paragraph This property contains the header type for EOT
		 * @brief QtCGI::ContentFontEOT
		 * @var QString
		 */
		static QString ContentFontEOT;

		/**
		 * @paragraph This property contains the header type for OTF
		 * @brief QtCGI::ContentFontOTF
		 * @var QString
		 */
		static QString ContentFontOTF;

		/**
		 * @paragraph This property contains the header type for TTF
		 * @brief QtCGI::ContentFontTTF
		 * @var QString
		 */
		static QString ContentFontTTF;

		/**
		 * @paragraph This property contains the header type for WOFF
		 * @brief QtCGI::ContentFontWOFF
		 * @var QString
		 */
		static QString ContentFontWOFF;

		/**
		 * @paragraph This property contains the header type for ECMAS
		 * @brief QtCGI::ContentScriptECMAS
		 * @var QString
		 */
		static QString ContentScriptECMAS;

		/**
		 * @paragraph This property contains the header type for VB
		 * @brief QtCGI::ContentScriptVB
		 * @var QString
		 */
		static QString ContentScriptVB;

		/**
		 * @paragraph This property contains the header type for CSS
		 * @brief QtCGI::ContentTypeCSS
		 * @var QString
		 */
		static QString ContentTypeCSS;

		/**
		 * @paragraph This property contain the header type for HTML
		 * @brief QtCGI::ContentTypeHTML
		 * @var QString
		 */
		static QString ContentTypeHTML;

		/**
		 * @paragraph This property contains the header type for JS
		 * @brief QtCGI::ContentTypeJS
		 * @var QString
		 */
		static QString ContentTypeJS;

		/**
		 * @paragraph This property contains the header type for JSON
		 * @brief QtCGI::ContentTypeJSON
		 * @var QString
		 */
		static QString ContentTypeJSON;

		/**
		 * @paragraph This property contains the header type for TXT
		 * @brief QtCGI::ContentTypeText
		 * @var QString
		 */
		static QString ContentTypeText;

		/**
		 * @paragraph This property contains the header type for XML
		 * @brief QtCGI::ContentTypeXML
		 * @var QString
		 */
		static QString ContentTypeXML;

		/**
		 * @paragraph This property contains the COMSPEC header name
		 * @brief QtCGI::HeaderComSpec
		 * @var QString
		 */
		static QString HeaderComSpec;

		/**
		 * @paragraph This property contains the DOCUMENT_ROOT header name
		 * @brief QtCGI::HeaderDocumentRoot
		 * @var QString
		 */
		static QString HeaderDocumentRoot;

		/**
		 * @paragraph This proeprty contains the GATEWAY_INTERFACE header name
		 * @brief QtCGI::HeaderGatewayInterface
		 * @var QString
		 */
		static QString HeaderGatewayInterface;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT header name
		 * @brief QtCGI::HeaderHttpAccept
		 * @var QString
		 */
		static QString HeaderHttpAccept;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT_ENCODING header name
		 * @brief QtCGI::HeaderHttpAcceptEncoding
		 * @var QString
		 */
		static QString HeaderHttpAcceptEncoding;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT_LANGUAGE header
		 * @brief QtCGI::HeaderHttpAcceptLanguage
		 * @var QString
		 */
		static QString HeaderHttpAcceptLanguage;

		/**
		 * @paragraph This property contains the HTTP_CONNECTION header name
		 * @brief QtCGI::HeaderHttpConnection
		 * @var QString
		 */
		static QString HeaderHttpConnection;

		/**
		 * @paragraph This property contains the HTTP_COOKIE header name
		 * @brief QtCGI::HeaderHttpCookie
		 * @var QString
		 */
		static QString HeaderHttpCookie;

		/**
		 * @paragraph This property contains the HTTP_HOST header name
		 * @brief QtCGI::HeaderHttpHost
		 * @var QString
		 */
		static QString HeaderHttpHost;

		/**
		 * @paragraph This property contains the HTTP_USER_AGENT header name
		 * @brief QtCGI::HeaderHttpUserAgent
		 * @var QString
		 */
		static QString HeaderHttpUserAgent;

		/**
		 * @paragraph This property contains the PATH header name
		 * @brief QtCGI::HeaderPath
		 */
		static QString HeaderPath;

		/**
		 * @paragraph This property contains the QUERY_STRING header name
		 * @brief QtCGI::eaderQueryString
		 * @var QString
		 */
		static QString HeaderQueryString;

		/**
		 * @paragraph This property contains the REMOTE_ADDR header name
		 * @brief QtCGI::HeaderRemoteAddress
		 * @var QString
		 */
		static QString HeaderRemoteAddress;

		/**
		 * @paragraph This property contain the REMOTE_PORT header name
		 * @brief QtCGI::HeaderRemotePort
		 * @var QString
		 */
		static QString HeaderRemotePort;

		/**
		 * @paragraph This property contains the REQUEST_METHOD header name
		 * @brief QtCGI::HeaderRequestMethod
		 * @var QString
		 */
		static QString HeaderRequestMethod;

		/**
		 * @paragraph This property contains the REQUEST_URI header name
		 * @brief QtCGI::HeaderRequestUri
		 * @var QString
		 */
		static QString HeaderRequestUri;

		/**
		 * @paragraph This paragraph contains the SCRIPT_FILENAME header name
		 * @brief QtCGI::HeaderScriptFilename
		 * @var QString
		 */
		static QString HeaderScriptFilename;

		/**
		 * @paragraph This property contains the SCRIPT_NAME header namr
		 * @brief QtCGI::HeaderScriptName
		 * @var QString
		 */
		static QString HeaderScriptName;

		/**
		 * @paragraph This property contains the SERVER_ADDR header name
		 * @brief QtCGI::HeaderServerAddress
		 * @var QString
		 */
		static QString HeaderServerAddress;

		/**
		 * @paragraph This property contians the SERVER_ADMIN header name
		 * @brief QtCGI::HeaderServerAdministrator
		 * @var QString
		 */
		static QString HeaderServerAdministrator;

		/**
		 * @paragraph This property contains the SERVER_NAME header name
		 * @brief QtCGI::HeaderServerName
		 * @var QString
		 */
		static QString HeaderServerName;

		/**
		 * @paragraph This property contains the SERVER_PORT header name
		 * @brief QtCGI::HeaderServerPort
		 * @var QString
		 */
		static QString HeaderServerPort;

		/**
		 * @paragraph This property contains the SERVER_PROTOCOL header name
		 * @brief QtCGI::HeaderServerProtocol
		 * @var QString
		 */
		static QString HeaderServerProtocol;

		/**
		 * @paragraph This property contains the SERVER_SIGNATURE header name
		 * @brief QtCGI::HeaderServerSignature
		 * @var QString
		 */
		static QString HeaderServerSignature;

		/**
		 * @paragraph This property contains the SERVER_SOFTWARE header name
		 * @brief QtCGI::HeaderServerSoftware
		 * @var QString
		 */
		static QString HeaderServerSoftware;

		/**
		 * @paragraph This property contains the DELETE data request method name
		 * @brief QtCGI::MethodDelete
		 * @var QString
		 */
		static QString MethodDelete;

		/**
		 * @paragraph This property contains the GET data request method name
		 * @brief QtCGI::MethodGet
		 * @var QString
		 */
		static QString MethodGet;

		/**
		 * @paragraph This property contains the HEAD data request method name
		 * @brief QtCGI::MethodHead
		 * @var QString
		 */
		static QString MethodHead;

		/**
		 * @paragraph This property contains the POST data request method name
		 * @brief QtCGI::MethodPost
		 * @var QString
		 */
		static QString MethodPost;

		/**
		 * @paragraph This property contains the PUT data request method name
		 * @brief QtCGI::MethodPut
		 * @var QString
		 */
		static QString MethodPut;

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief QtCGI::Instance()
		 * @param bool bReset [false]
		 * @param QObject* qoParent [0]
		 * @return QtCGI* QtCGI::mInstance
		 */
		static QtCGI* Instance(bool bReset = false, QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor autmatically parses the HTTP headers and data
		 * @brief QtCGI::QtCGI()
		 * @param QObject* qoParent [0]
		 */
		explicit QtCGI(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a response header to the instance
		 * @brief QtCGI::AddResponseHeader()
		 * @param QString strName
		 * @param QString strValue
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* AddResponseHeader(QString strName, QString strValue);

		/**
		 * @paragraph This method decodes a query string into a query map
		 * @brief QtCGI::DecodeQuery()
		 * @param QString strQuery
		 * @param QString strPairSeparator ["&"]
		 * @return QMap<QString, QString>
		 */
		QMap<QString, QString> DecodeQuery(QString strQuery, QString strPairSeparator = "&");

		/**
		 * @paragraph This method encodes a query map into a query string
		 * @brief QtCGI::EncodeQuery()
		 * @param QMap<QString, QString> qmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
		QString EncodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue = "&");

		/**
		 * @paragraph This method encodes a query variant map into a query string
		 * @brief QtCGI::EncodeQuery()
		 * @param QVariantMap qvmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
		QString EncodeQuery(QVariantMap qvmQuery, QString strPairGlue = "&");

		/**
		 * @paragraph This method writes the HTTP response to the browser/socket
		 * @brief QtCGI::WriteResponse()
		 * @return void
		 */
		void WriteResponse();

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the current response content in the instance
		 * @brief QtCGI::GetContent()
		 * @return QString QtCGI::mContent
		 */
		QString GetContent();

		/**
		 * @paragraph This method returns a cookie from the instance if one exists
		 * @brief QtCGI::GetCookie()
		 * @param QString strName
		 * @return QString
		 */
		QString GetCookie(QString strName);

		/**
		 * @paragraph This method returns the current cookie map in the instance
		 * @brief QtCGI::GetCookies()
		 * @return QMap<QString, QString> QtCGI::mCookies
		 */
		QMap<QString, QString> GetCookies();

		/**
		 * @paragraph This method returns a GET/POST parameter from the instance if one exists
		 * @brief QtCGI::GetParam()
		 * @param QString strName
		 * @return QString
		 */
		QString GetParam(QString strName);

		/**
		 * @paragraph This method returns the current POST map from the instance
		 * @brief QtCGI::GetPostData()
		 * @return QMap<QString, QString> QtCGI::mPostParameters
		 */
		QMap<QString, QString> GetPostData();

		/**
		 * @paragraph This method returns the current GET map from the instance
		 * @brief QtCGI::GetQueryData()
		 * @return QMap<QString, QString> QtCGI::mGetParameters
		 */
		QMap<QString, QString> GetQueryData();

		/**
		 * @paragraph This method returns a request header from the instance if one exists
		 * @brief QtCGI::GetRequestHeader()
		 * @param QString strName
		 * @return QString
		 */
		QString GetRequestHeader(QString strName);

		/**
		 * @paragraph This method returns the current request header map in the instance
		 * @brief QtCGI::GetRequestHeaders()
		 * @return QMap<QString, QString> QtCGI::mRequestHeaders
		 */
		QMap<QString, QString> GetRequestHeaders();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the response content into the instance
		 * @brief QtCGI::SetContent()
		 * @param QString strContent
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* SetContent(QString strContent);

		/**
		 * @paragraph This method sets the content type header into the instance
		 * @brief QtCGI::SetContentType()
		 * @param QString strContentType
		 * @return QtCGI* QtCGI::mInstance
		 */
		QtCGI* SetContentType(QString strContentType = QtCGI::ContentTypeHTML);

	signals:

	public slots:

};

#endif // QtCGI_H
