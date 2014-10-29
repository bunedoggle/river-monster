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

#include "eoArchive.h"
#include "eoHeader.h"

eoArchive::eoArchive()
{
	isStoring = false;
	h = 0;
	isName = false;
	state = 0;
	level = 0;
}

eoArchive::~eoArchive()
{
	Close();
}

uint8_t eoArchive::Open(const char * strBuf)
{
	return NOT_IMPLEMENTED;
}

void eoArchive::indent()
{

}

void eoArchive::startBlock(const char* blockName)
{

}

void eoArchive::startBlock()
{

}
void eoArchive::endBlock()
{

}

void eoArchive::Close()
{

}

eoArchive& eoArchive::operator &(char *obj)
{
	return *this;
}
eoArchive& eoArchive::operator &(char const *obj)
{
	return *this;
}

eoArchive & eoArchive::operator &(uint16_t &obj)
{
	return *this;
}
eoArchive & eoArchive::operator &(int16_t &obj)
{

	return *this;
}

eoArchive & eoArchive::operator &(uint32_t &obj)
{
	return *this;
}

eoArchive & eoArchive::operator &(int32_t &obj)
{
	return *this;
}

eoArchive & eoArchive::operator &(float &obj)
{
	return *this;
}

eoArchive & eoArchive::operator &(uint8_t &obj)
{
	return *this;
}
eoArchive & eoArchive::operator &(int8_t &obj)
{
	return *this;
}

eoArchive & eoArchive::operator &(bool &obj)
{
	return *this;
}

eoArchive& eoArchive::operator &(eoISerialize *obj)
{
	return *this;
}

eoArchive & eoArchive::operator &(eoISerialize &obj)
{
	return *this;
}

