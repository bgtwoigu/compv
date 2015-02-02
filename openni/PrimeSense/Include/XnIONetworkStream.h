/*****************************************************************************
*                                                                            *
*  PrimeSense Sensor 5.x Alpha                                               *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of PrimeSense Sensor                                    *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#ifndef __XN_IO_NETWORK_STREAM_H__
#define __XN_IO_NETWORK_STREAM_H__

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnIOStream.h>
#include <XnOS.h>

//---------------------------------------------------------------------------
// Types
//---------------------------------------------------------------------------
class XN_CORE_CPP_API XnIONetworkStream : public XnIOStream
{
public:
	XnIONetworkStream(XN_SOCKET_HANDLE hSocket);
	~XnIONetworkStream() { Free(); }

	virtual XnStatus WriteData(const XnUChar* pData, XnUInt32 nDataSize);
	virtual XnStatus ReadData(XnUChar* pData, XnUInt32 nDataSize);
	virtual XnStatus Init();
	virtual XnStatus Free();
	inline XnBool IsConnected() const { return m_bIsConnected; }
	void SetReadTimeout(XnUInt32 nMicrosecondsReadTimeout);

private:
	XnUInt32 m_nReadTimeout;
	XN_SOCKET_HANDLE m_hSocket;
	XnBool m_bIsConnected;

};

#endif //__XN_IO_NETWORK_STREAM_H__