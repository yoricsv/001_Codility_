//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef FILE_INSTANCE_H
#define FILE_INSTANCE_H

#include <string>
#include <fstream>

#include "IFileInstance.h"
/**
class FileInstance :
    public IFileInstance
{
private:


public static FileInstance getInstance()
{
    return instance;
}

public static FileInstance getInstance(String initPath)
{
if (instance == null)
instance = new FileInstance(initPath);

return instance;
}

private void instanceFault()
{
    logger.error(
            "ERROR!\t File or Directory creation fault!\n" +
            "\t\tCheck The Path and Access rights"
    );
    instance = null;
}

@Override
public File getFile()
{
    return this.filePointer;
}

private static final String FILE_NAME     = "visits.dat";
private: static const int THE_FIRST_HIT = 1;

private static FileInstance instance      = nullptr;
private                File filePointer   = null;

private:
    std::fstream _file;

    explicit FileInstance(const std::string & initPath)         // PRIVATE CONSTRUCTOR
    {
        try
        {
            filePointer = new File(initPath + FILE_NAME);

            if(checkAccessToFile(filePointer))
            {
                BufferedWriter fbw =
                        new BufferedWriter(
                                new FileWriter(filePointer)
                        );

                fbw.write(String.valueOf(THE_FIRST_HIT));

                fbw.flush();
                fbw.close();
            }
            else
                instanceFault();
        }
        catch (IOException e)
        {
            logger.error(e.toString(), e);
        }
    }

bool checkAccessToFile(File filePtr)
    {
        if(filePtr.exists())
            return     filePtr.canRead()
                       && filePtr.canWrite();
        else
        {
            try
            {
                return     filePtr.getParentFile().mkdirs()
                           && filePtr.createNewFile()
                           && filePtr.canRead()
                           && filePtr.canWrite();
            }
            catch (IOException e)
            {
                logger.trace(e.toString(), e);
            }
        }
        return false;
    }

}
*/
#endif //FILE_INSTANCE_H
