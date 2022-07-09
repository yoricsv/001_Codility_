//
// Created by Yoric on 25-Feb-22.
//
#include "FileSystem.h"
/**
static std::string size_string(size_t file_size)
{
    std::stringstream string_stream;

    if (file_size >= 1000000000)
        string_stream
                << (file_size / 1000000000)
                << DELIMITER << 'G' << 'b';
    else if (file_size >= 1000000)
        string_stream
                << (file_size / 1000000)
                << DELIMITER << 'M' << 'b';
    else
        if (file_size >= 1000)
        string_stream
                << (file_size / 1000)
                << DELIMITER << 'K' << 'b';
    else
        string_stream
            << file_size
            << DELIMITER << 'b' ;

    return string_stream.str();
}

std::string detectGroup(
        const std::string              & file_extension,
        const std::map<std::string,std::string> & pairs
    )
{
    std::string type  = file_extension;
    auto it = pairs.find(type.erase(0, 1));

    return it != pairs.end() ? it -> second : "other";
}
*/


/** TEST cutDotInExtension() */
//    std::vector<std::string>test {
//        "._txt",                          // _txt
//        "something.something_txt",        // something_txt
//        "..something.__something_txt",    // __something_txt
//        "txt",                            // txt
//        ""                                // <displayed only \n>
//    };
//    for(const auto & i : test)
//        std::cout << cutDotInExtension(i) << std::endl;

/*
std::map<std::string, std::string>              type_group;
std::map<std::string, std::vector<std::string>> output_list;
 std::map<std::string, std::vector<std::string>> output_list;

void sortExtensionsByGroups(
//std::map<std::string, std::vector<std::string>> sortExtensionsByGroups(
        const std::string                                       & extension,
        const std::map<std::string, std::string>                & pairs//,
        //const std::map<std::string, std::vector<std::string>>   & output
)
{
    std::map<std::string, std::vector<std::string>> grouping_tmp;

    const std::string              group    { detectGroup(extension, pairs) };
//    const std::vector<std::string> ext_list { extension };
//    auto & [ext] = grouping_tmp[group];

    grouping_tmp[group].push_back({extension});

//    return grouping_tmp;
}

//    std::vector<std::string> groups {"documents", "movies", "music", "other", "pictures", "programs"};

using map_type = std::map< std::string, std::vector<std::string>> ;

void query(
        const map_type   & mmap,
        const std::string & key
)
{
    std::cout << "query key: " << key << "\n\n" ;

    const auto pair = mmap.equal_range(key) ;

    if( pair.first == mmap.end() )
        std::cout << " *** not found ***\n" ;

    else
        for( auto iter = pair.first ; iter != pair.second ; ++iter )
        {
            for( const auto& str : iter->second )
                std::cout << std::quoted(str) << ' ' ;

        }
    std::cout << "\n--------------\n\n" ;
}


        sortExtensionsByGroups(extension, type_group);


//std::multimap<std::string, std::map<fs::path, std::pair<size_t, size_t>>> sortExtensionsByGroups(
//        const std::map<fs::path, std::pair<size_t, size_t>> & result_tmp_map,
//        const std::map<std::string,std::string> & pairs
//        )
//{
//    std::multimap<std::string, std::map<fs::path, std::pair<size_t, size_t>>> grouping;
//
//    for (const auto & [extension, status] : result_tmp_map)
//    {
//        const std::string group =
//            detectGroup(
//                cutDotInExtension(extension.string()),
//                pairs
//            );
//
//        auto & [groups, result_map] = grouping[group];
//
//        auto it = result_tmp_map.find(cutDotInExtension(extension.string()));
//
//        grouping.emplace("",it != result_tmp_map.end() ? it -> second : "other");
//    }
//
//    return grouping;
//}
 //        for ( const auto & i : groups)
//        {
//            if( detectGroup(
//                    cutDotInExtension(extension.string()),
//                    type_group
//                ) == i)

 //        void query( const map_type& map, const std::string& key )
//        {
//            std::cout << "query on key: " << std::quoted(key) << "\n\n" ;
//
//            const auto iter = map.find(key) ;
//            if( iter == map.end() ) std::cout << "*** not found ***\n" ;
//            else print( iter->second ) ;
//        }

//        for( const auto & [group, ext] : output_list )
//        {
//            const auto iter = output_list.find(group) ;
//            if( iter == output_list.end() ) std::cout << "*** not found ***\n" ;
//            else print( iter -> second ) ;
//            const auto & [index, value] = ext;
//
//
//            return iter != output_list.end() ? iter -> second : "other";
//            std::cout << "[ " ;
//            for( const auto& str : rec ) std::cout << std::quoted(str) << ' ' ;
//            std::cout << "]\n" ;
//        }


                 for (const auto & i : output_list)
                {
                    query(output_list, i.first);
                }
*/
