/******************************************************************************
 DISCLAIMER

 THIS SOFTWARE PRODUCT ("SOFTWARE") IS PROPRIETARY TO ENOCEAN GMBH, OBERHACHING,
 GERMANY (THE "OWNER") AND IS PROTECTED BY COPYRIGHT AND INTERNATIONAL TREATIES OR
 PROTECTED AS TRADE SECRET OR AS OTHER INTELLECTUAL PROPERTY RIGHT. ALL RIGHTS, TITLE AND
 INTEREST IN AND TO THE SOFTWARE, INCLUDING ANY COPYRIGHT, TRADE SECRET OR ANY OTHER 
 INTELLECTUAL PROPERTY EMBODIED IN THE SOFTWARE, AND ANY RIGHTS TO REPRODUCE,
 DISTRIBUTE, MODIFY, DISPLAY OR OTHERWISE USE THE SOFTWARE SHALL EXCLUSIVELY VEST IN THE
 OWNER. ANY UNAUTHORIZED REPRODUCTION, DISTRIBUTION, MODIFICATION, DISPLAY OR OTHER
 USE OF THE SOFTWARE WITHOUT THE EXPLICIT PERMISSION OF OWNER IS PROHIBITED AND WILL 
 CONSTITUTE AN INFRINGEMENT OF THE OWNER'S RIGHT AND MAY BE SUBJECT TO CIVIL OR
 CRIMINAL SANCTION.

 THIS SOFTWARE IS PROVIDED BY THE OWNER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN PARTICULAR, THE OWNER DOES NOT WARRANT
 THAT THE SOFTWARE SHALL BE ERROR FREE AND WORKS WITHOUT INTERRUPTION.

 IN NO EVENT SHALL THE OWNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/
#include "eoGateway.h"
#include "eoTimer.h"
#include "eoConverter.h"
#include "eoLinuxPacketStream.h"
#include "eoFilterFactory.h"
#include "eoConverter.h"

void eoGateway::defaultConstructor()
{
	flags = 0;
	errorCode = 0;
	stream = NULL;
	device = NULL;
	filter = NULL;
	learnFilter = NULL;
	deviceManager = NULL;
	LearnMode = false;
	TeachInModule = NULL;
}

eoGateway::eoGateway() :
		packet(512), telegram(14), message(512), commands(this)
{
	defaultConstructor();
	stream = new eoLinuxPacketStream();
	deviceManager = new eoDeviceManager();
	TeachInModule = new eoTeachInModule(deviceManager);
}

eoGateway::eoGateway(eoDeviceManager *devManager) :
		packet(512), telegram(14), message(512), commands(this)
{
	defaultConstructor();
	stream = new eoLinuxPacketStream();
	deviceManager = devManager;
	TeachInModule = new eoTeachInModule(deviceManager);
}

eoGateway::eoGateway(eoPacketStream *str) :
		packet(512), telegram(14), message(512), commands(this)
{
	defaultConstructor();
	stream = str;
	deviceManager = new eoDeviceManager();
	TeachInModule = new eoTeachInModule(deviceManager);
}

eoGateway::eoGateway(eoPacketStream *str, eoDeviceManager *devManager) :
		packet(512), telegram(14), message(512), commands(this)
{
	defaultConstructor();
	stream = str;
	deviceManager = devManager;
	TeachInModule = new eoTeachInModule(deviceManager);
}

eoGateway::eoGateway(eoPacketStream *str, eoDeviceManager *devManager, eoIFilter * normFilter, eoIFilter * lrnFilter) :
		packet(512), telegram(14), message(512), commands(this)
{
	defaultConstructor();
	stream = str;
	filter = normFilter;
	TeachInModule = new eoTeachInModule(deviceManager);
}

eoGateway::~eoGateway()
{

	if (stream != NULL)
		delete stream;
	stream = NULL;

	if (TeachInModule != NULL)
		delete TeachInModule;
	TeachInModule = NULL;

	if (deviceManager != NULL)
		delete deviceManager;
	deviceManager = NULL;
	if (filter != NULL)
		delete filter;
	filter = NULL;
	if (learnFilter != NULL)
		delete learnFilter;
	learnFilter = NULL;

	std::deque<eoPacket*>::iterator it;
	for (it = packet_queue.begin(); it != packet_queue.end(); it++)
  		delete (*it);

	packet_queue.clear();
}

eoReturn eoGateway::secHandler(eoTelegram &recvTelegram)
{
	eoReturn errorCode = EO_ERROR;
	return errorCode;

}

eoReturn eoGateway::learnHandler(eoTelegram &recvTelegram)
{
	eoReturn ret = EO_OK;

	if (learnFilter != NULL && !learnFilter->Filter(recvTelegram)) //
	{
		flags &= (~RECV_TELEGRAM);
	}
	else
	{
		ret = recvTelegram.copyTo(message);

		if (ret == EO_OK)
		{
			flags |= RECV_MESSAGE;

			TEACH_RETURN teachRet;

			teachRet = TeachInModule->TeachIN(message);
			if (device == NULL)
				device = deviceManager->Get(recvTelegram.sourceID);
			if (teachRet == NEW_DEVICE_AND_EPP)
				flags |= RECV_DEVICE_ADDED;
			if (teachRet == EEP_TEACH_IN || teachRet == NEW_DEVICE_AND_EPP)
				flags |= RECV_TEACHIN;
			if (teachRet == SECOND_TEACH_IN)
				flags |= RECV_SECTEACHIN;
		}
	}
	return ret;
}

eoReturn eoGateway::normalHandler(eoTelegram &recvTelegram)
{
	eoReturn ret = EO_OK;

	if (filter != NULL && !filter->Filter(recvTelegram))
	{
		flags &= (~RECV_TELEGRAM);
	}
	else
	{
		if(TeachInModule->isTeachedIN(recvTelegram))
			flags |= RECV_SECTEACHIN;
		else if (eoTeachInModule::isTeachIN(recvTelegram))
			flags |= RECV_TEACHIN;

		ret = recvTelegram.copyTo(message);
		if (ret == EO_OK)
			flags |= RECV_MESSAGE;
	}
	return ret;
}

uint16_t eoGateway::Receive()
{
	flags = 0;
	// Process the packet from the queue or receive one from UART
	if (!packet_queue.empty())
	{
		eoPacket *p = packet_queue.front();
		p->copyTo(packet);
		delete p;
		packet_queue.pop_front();
	}
	else
	{
		errorCode = (uint8_t)stream->Receive(&packet);
		if (errorCode != EO_OK)
			return flags;
	}
	flags = RECV_PACKET;


	errorCode = (uint8_t)eoConverter::packetToRadio(packet, telegram);

	if (errorCode == EO_OK)
		flags |= RECV_TELEGRAM;
	else
		return flags;
	device = deviceManager->Get(telegram.sourceID);

	if (LearnMode)
		errorCode = (uint8_t)learnHandler(telegram);
	else
		errorCode = (uint8_t)normalHandler(telegram);

	if (device != NULL && (flags & RECV_MESSAGE))
	{
		if (device->GetProfile()->Parse(message) == EO_OK)
		{
			flags |= RECV_PROFILE;
		}
	}
	return flags;
}

eoReturn eoGateway::Send(const eoPacket &p)
{
	eoReturn ret;

	flags = 0;

	ret = stream->Send(p);

	if (ret != EO_OK)
		return ret;

	// We send response command, so we don't expect response from controller
	if (p.type == PACKET_RESPONSE)
		return EO_OK;

	// Wait for the response for max 500ms.
	uint32_t timeout = eoTimer::GetTickCount() + 500;

	while (eoTimer::GetTickCount() < timeout)
	{
		if (stream->Receive(&packet) != EO_OK)
			continue;

		if (packet.type == PACKET_RESPONSE)
		{
			flags = RECV_PACKET;
			return (eoReturn) packet.data[0]; // The ESP3 response codes are the same as the eoReturn codes
		}

		eoPacket *p = new eoPacket(packet);
		packet_queue.push_back(p);
	}

	return TIME_OUT;
}

eoReturn eoGateway::Send(const eoMessage &msg)
{
	if ((msg.GetDataLength() <= 14 && msg.destinationID == BROADCAST_ID) ||
		(msg.GetDataLength() <= 9  && msg.destinationID != BROADCAST_ID))
	{
		if (eoConverter::radioToPacket(msg, packet) != EO_OK)
			return EO_ERROR;

		return Send(packet);
	}
	return EO_ERROR;
}

eoReturn eoGateway::Open(const char *port)
{
	return stream->Open(port);
}

void eoGateway::Close()
{
	stream->Close();
}

uint8_t eoGateway::Serialize(eoArchive &arch)
{
	arch & "myDeviceManager" & deviceManager;
	if (arch.isStoring)
	{
		arch & "myFilter" & filter;
		arch & "myLearnFilter" & learnFilter;
	}
	else
	{
		eoIFilter tmpFilter;
		eoIFilter* newPointedFilter=NULL;
		arch & "myFilter" & tmpFilter;
		newPointedFilter = eoFilterFactory::CreateFilter(tmpFilter.type);
		if (newPointedFilter != NULL)
		{
			if (filter ==  NULL)
				filter = newPointedFilter;
			else
				delete newPointedFilter;

			filter->RemoveAll();
			arch & "myFilter" & filter;
		}

		arch & "myLearnFilter" & tmpFilter;
		newPointedFilter = eoFilterFactory::CreateFilter(tmpFilter.type);
		if (newPointedFilter != NULL)
		{
			if(learnFilter == NULL)
				filter = newPointedFilter;
			else
				delete newPointedFilter;
			learnFilter->RemoveAll();
			arch & "myLearnFilter" & learnFilter;
		}
	}
	arch & "LearnMode" & LearnMode;
	return EO_OK;
}
