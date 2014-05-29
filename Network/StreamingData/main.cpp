/* Copyright (c) 2014, The Nuria Project
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *    1. The origin of this software must not be misrepresented; you must not
 *       claim that you wrote the original software. If you use this software
 *       in a product, an acknowledgment in the product documentation would be
 *       appreciated but is not required.
 *    2. Altered source versions must be plainly marked as such, and must not be
 *       misrepresented as being the original software.
 *    3. This notice may not be removed or altered from any source
 *       distribution.
 */

#include <QGuiApplication>

#include <nuria/httpclient.hpp>
#include <nuria/httpserver.hpp>
#include <nuria/httpnode.hpp>
#include <nuria/debug.hpp>
#include <QUrlQuery>
#include <QPainter>
#include <QBuffer>
#include <QImage>

/*******************************************************************************
 * This is an example for the Nuria Framework.
 * You can find the description under:
 * https://github.com/NuriaProject/FrameworkExamples/wiki/Streaming-Data
 ******************************************************************************/

static void renderSlot (Nuria::HttpClient *client) {
	
	// [2]
	QUrlQuery query (client->path ());
	QString textToPrint = query.queryItemValue ("text");
	
	// [3]
	QImage image (400, 100, QImage::Format_ARGB32_Premultiplied);
	image.fill (Qt::white);
	
	// [4]
	QPainter painter (&image);
	painter.drawText (image.rect (), textToPrint);
	painter.end ();
	
	// [5]
	QBuffer *buffer = new QBuffer;
	buffer->open (QIODevice::ReadWrite);
	image.save (buffer, "PNG");
	
	// [6]
	buffer->reset ();
	client->pipeToClient (buffer);
	
}

int main (int argc, char *argv[]) {
	QGuiApplication a (argc, argv);
	
	// [1]
	Nuria::HttpServer server;
	
	QDir staticsDir (SOURCE_PATH "/static");
	server.root ()->setStaticResourceDir (staticsDir);
	server.root ()->setStaticResourceMode (Nuria::HttpNode::UseStaticResources);
	
	// [7]
	server.root ()->connectSlot ("render", renderSlot);
	
	// [8]
	if (!server.listen (QHostAddress::Any, 8080)) {
		qDebug("Failed to listen on port 8080.");
		return 1;
	}
	
	qDebug("Running. Now go to http://127.0.0.1:8080/");
	return a.exec ();
}
