#include "tsCommon.h"
#include "tsTransportStream.h"
#include <cstdio>

int main( int argc, char *argv[ ], char *envp[ ])
{
    const char* filename = "../example_new.ts";
    FILE* TransportStreamFile = fopen(filename, "rb");
    if (TransportStreamFile == NULL)
    {
        printf("wrong file name\n");
        return EXIT_FAILURE;
    }

  xTS_PacketHeader    TS_PacketHeader;
  xTS_AdaptationField TS_AdaptationField;
  uint8_t* TS_PacketBuffer = (uint8_t*)malloc(sizeof(uint8_t) * 188);  //buffer memory allocation

  int32_t TS_PacketId = 0;
  while(!feof(TransportStreamFile))
  {
    fread(TS_PacketBuffer, 188, 1, TransportStreamFile);  //read from file

    TS_PacketHeader.Reset();
    TS_PacketHeader.Parse(TS_PacketBuffer);

    printf("%010d ", TS_PacketId);
    TS_PacketHeader.Print();

    if (TS_PacketHeader.hasAdaptationField()) 
    {
        TS_AdaptationField.Reset();
        TS_AdaptationField.Parse(TS_PacketBuffer, TS_PacketHeader.getAFC());
        TS_AdaptationField.Print();
    }

    printf("\n");

    TS_PacketId++;
  }

  fclose(TransportStreamFile);
}