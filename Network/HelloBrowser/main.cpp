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

#include <QCoreApplication>

#include <nuria/httpclient.hpp>
#include <nuria/httpserver.hpp>
#include <nuria/httpnode.hpp>
#include <nuria/logger.hpp>

/*******************************************************************************
 * This is an example for the Nuria Framework.
 * You can find the description under:
 * https://github.com/NuriaProject/FrameworkExamples/wiki/Hello-Browser
 ******************************************************************************/

// [2]
void mySlot (Nuria::HttpClient *client) {
	client->write ("<h1>Hello world</h1>");
}

int main (int argc, char *argv[]) {
	QCoreApplication a (argc, argv);
	
	// [1]
	Nuria::HttpServer server;
	
	// [3]
	server.root ()->connectSlot ("index", mySlot);
	
	// [4]
	if (!server.listen (QHostAddress::Any, 8080)) {
		nError() << "Failed to listen on port 8080.";
		return 1;
	}
	
	nLog() << "Running. Now go to http://127.0.0.1:8080/";
	return a.exec ();
}
