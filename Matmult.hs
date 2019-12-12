{-# LANGUAGE ViewPatterns, ScopedTypeVariables #-}
import Foreign.C
import Foreign.Ptr
import Test.QuickCheck
import Foreign.Marshal.Array
import Data.List
import System.IO.Unsafe
import Control.Monad

newtype NineList = NineList [CInt] deriving (Show)

instance Arbitrary NineList where
  arbitrary = NineList <$> replicateM 9 arbitrary

foreign import ccall "_Z7matmultPiS_ii" matmultImpl :: Ptr CInt -> Ptr CInt -> CInt -> CInt -> IO (Ptr CInt)

foreign import ccall "_Z7initOctv" initOct :: IO ()

matmult :: [CInt] -> [CInt] -> [CInt]
matmult xs ys = unsafePerformIO $ do
  xs' <- newArray xs
  ys' <- newArray ys
  ret <- matmultImpl xs' ys' (genericLength xs) (genericLength ys)
  peekArray 9 ret

xs = [1..9]

main :: IO ()
main = do
  initOct
  quickCheck $ \(NineList x) (NineList y) -> matmult x y === matmult y x
