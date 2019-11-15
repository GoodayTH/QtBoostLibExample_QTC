#ifndef ASIOCLIENT_H
#define ASIOCLIENT_H

#include <boost\asio.hpp>
#include <boost/bind.hpp>

#include <QObject>
#include <QString>
#include <memory>
#include <thread>

class AsioClient
{
public:
    AsioClient();
    virtual ~AsioClient();

    void Get(const QString& url, const QString& path);
    void handle_resolve(const boost::system::error_code& err,
                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    void handle_connect(const boost::system::error_code& err,
                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    void handle_write(const boost::system::error_code& err);
    void handle_read_line(const boost::system::error_code& err);
    void handle_read_header(const boost::system::error_code& err);
    void handle_read_content(const boost::system::error_code& err);

private:
    boost::asio::io_service ioservice;
    std::shared_ptr<boost::asio::io_service::work> work;
    std::thread worker;

    std::string server, path;
    boost::asio::ip::tcp::resolver resolver;

    boost::asio::ip::tcp::socket socket;

    boost::asio::streambuf requestbuf;
    boost::asio::streambuf responsebuf;

    std::ostringstream oss;
};

#endif // ASIOCLIENT_H
