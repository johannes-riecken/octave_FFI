import Foreign.C
import Test.QuickCheck

foreign import ccall "_Z3gcdii" myGcd :: CInt -> CInt -> CInt

foreign import ccall "_Z7initOctv" initOct :: IO ()

main :: IO ()
main = do
  initOct
  quickCheck $ \x y -> myGcd x y === gcd x y
