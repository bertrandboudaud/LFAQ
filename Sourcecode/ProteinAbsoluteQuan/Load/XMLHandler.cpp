// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2013.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Chris Bielow $
// $Authors: Marc Sturm, Chris Bielow $
// --------------------------------------------------------------------------

#include"stdafx.h"
#include "XMLHandler.h"




XMLHandler::XMLHandler(const string & filename) :
error_message_(""),
file_(filename)
{
}

XMLHandler::~XMLHandler()
{
}

void XMLHandler::reset() // reset Xerces XML strings (memleak otherwise)
{
	for (size_t i = 0; i < xml_strings_.size(); ++i)
	{
		XMLString::release(&xml_strings_[i]);
	}
	xml_strings_.clear();

	for (size_t i = 0; i < c_strings_.size(); ++i)
	{
		XMLString::release(&c_strings_[i]);
	}
	c_strings_.clear();
}

void XMLHandler::characters(const XMLCh * const /*chars*/, const XMLSize_t /*length*/)
{
}

void XMLHandler::startElement(const XMLCh * const /*uri*/, const XMLCh * const /*localname*/, const XMLCh * const /*qname*/, const Attributes & /*attrs*/)
{
}

void XMLHandler::endElement(const XMLCh * const /*uri*/, const XMLCh * const /*localname*/, const XMLCh * const /*qname*/)
{
}
