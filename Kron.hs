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

foreign import ccall "_Z4kronPiS_iiii" kronImpl :: Ptr CInt -> Ptr CInt -> CInt -> CInt -> CInt -> CInt -> IO (Ptr CInt)

foreign import ccall "_Z7initOctv" initOct :: IO ()

kron :: [CInt] -> [CInt] -> CInt -> CInt -> CInt -> CInt -> [CInt]
kron xs ys xs_rows xs_cols ys_rows ys_cols = unsafePerformIO $ do
  xs' <- newArray xs
  ys' <- newArray ys
  ret <- kronImpl xs' ys' xs_rows xs_cols ys_rows ys_cols
  peekArray (fromIntegral $ xs_rows * xs_cols * ys_rows * ys_cols) ret

xs = [1..9]

main :: IO ()
main = do
  initOct
  print $ kron [1..4] [1..6] 2 2 2 3
