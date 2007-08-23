/*MT*
    
    MediaTomb - http://www.mediatomb.cc/
    
    youtube_service.h - this file is part of MediaTomb.
    
    Copyright (C) 2005 Gena Batyan <bgeradz@mediatomb.cc>,
                       Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>
    
    Copyright (C) 2006-2007 Gena Batyan <bgeradz@mediatomb.cc>,
                            Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>,
                            Leonhard Wimmer <leo@mediatomb.cc>
    
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.
    
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    version 2 along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
    
    $Id$
*/

/// \file youtube_service.h
/// \brief Definition of the YouTubeService class.

#if defined(YOUTUBE) // make sure to add more ifdefs when we get more services

#ifndef __YOUTUBE_SERVICE_H__
#define __YOUTUBE_SERVICE_H__

#include "zmm/zmm.h"
#include "mxml/mxml.h"
#include "online_service.h"
#include "get_url.h"
#include "dictionary.h"

/// \brief This is an interface for all online services, the function
/// handles adding/refreshing content in the database.
class YouTubeService : public OnlineService
{
public:
    YouTubeService();
    ~YouTubeService();
    /// \brief Retrieves user specified content from the service and adds
    /// the items to the database.
    virtual bool refreshServiceData(zmm::Ref<Layout> layout);
    virtual service_type_t getServiceType();
    virtual zmm::String getServiceName();
    virtual zmm::Ref<zmm::Object> defineServiceTask(zmm::Ref<mxml::Element> xmlopt);

protected:
    // the handle *must never be used from multiple threads*
    CURL *curl_handle;
    // safeguard to ensure the above
    pthread_t pid;

    // url retriever class
    zmm::Ref<GetURL> url;

    /// \brief This function will retrieve the XML according to the parametrs
    zmm::Ref<mxml::Element> getData(zmm::Ref<Dictionary> params);

    enum methods_t
    {
        YT_none,
        YT_list_favorite,
        YT_list_by_tag,
        YT_list_by_user,
        YT_list_featured,
        YT_list_by_playlist,
        YT_list_popular,
        YT_list_by_category_and_tag
    };


    class YouTubeTask : public zmm::Object
    {
    public:
        YouTubeTask() 
        { 
            parameters = zmm::Ref<Dictionary>(new Dictionary());
            method = YT_none;
            amount = 0;
        }

        methods_t method;
        zmm::Ref<Dictionary> parameters;
        int amount;
    };

    zmm::String getCheckAttr(zmm::Ref<mxml::Element> xml, zmm::String attrname);
    int getCheckPosIntAttr(zmm::Ref<mxml::Element> xml, zmm::String attrname);
    void addPagingParams(zmm::Ref<mxml::Element> xml, 
                         zmm::Ref<YouTubeTask> task);
};

#endif//__ONLINE_SERVICE_H__

#endif//YOUTUBE