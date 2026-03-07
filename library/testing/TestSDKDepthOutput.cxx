#include <image.h>

#include "PseudoUnitTest.h"

#include <string>

int TestSDKDepthOutput([[maybe_unused]] int argc, char* argv[])
{
  PseudoUnitTest test;

  f3d::image depthImage;
  test("read generated depth png", [&]() {
    depthImage = f3d::image(std::string(argv[2]) + "TestDepthOutputDepth.png");
  });

  if (test.result() != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }

  test("depth image has width", depthImage.getWidth() > 0);
  test("depth image has height", depthImage.getHeight() > 0);
  test("depth image uses a single channel", depthImage.getChannelCount() == 1);
  test("depth image uses 16-bit channels",
    depthImage.getChannelType() == f3d::image::ChannelType::SHORT);

  const auto* depthPtr = static_cast<const unsigned short*>(depthImage.getContent());
  test("depth image buffer is accessible", depthPtr != nullptr);

  return test.result();
}
